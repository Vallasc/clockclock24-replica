#if defined(NVS_USE_LITTLEFS)
  #include "LittleFS.h"
  #define FS LittleFS
#else
  #include "FS.h"
  #define FS SPIFFS
#endif

static bool _fs_init() {
    bool res = FS.begin();
#ifdef NVS_USE_SPIFFS
    // Increase reliability for SPIFFS
    FS.check();
#endif
    return res;
}

static bool _fs_mkdir(const char *path) {
    // Path are automatically created as needed
    return true;
}

static bool verifyContent(File& f, const void* buf, int bufsize) {
    // TODO: read in chunks, remove this limitation
    if (f.size() == bufsize && bufsize <= 1024) {
        // Check if content is the same
        uint8_t tmp[bufsize];
        if (f.read((uint8_t*)tmp, bufsize) == bufsize) {
            if (!memcmp(buf, tmp, bufsize)) {
                return true;
            }
        }
    }
    return false;
}

static bool _fs_verify(const char* path, const void* buf, int bufsize) {
    if (File f = FS.open(path, "r")) {
        return verifyContent(f, buf, bufsize);
    }
    return false;
}

static int _fs_create(const char* path, const void* buf, int bufsize) {
    if (File f = FS.open(path, "w")) {
        return f.write((const uint8_t*)buf, bufsize);
    }
    return -1;
}

static int _fs_update(const char* path, const void* buf, int bufsize) {
    if (File f = FS.open(path, "r+")) {
        if (verifyContent(f, buf, bufsize)) {
            LOG_I("data matches, skip writing to %s", path);
            return bufsize;
        }
        if (f.size() <= bufsize) {
            f.seek(0, SeekSet);
            return f.write((const uint8_t*)buf, bufsize);
        }
    }
    return _fs_create(path, buf, bufsize);
}

static int _fs_read(const char* path, void* buf, int bufsize) {
    if (File f = FS.open(path, "r")) {
        return f.read((uint8_t*)buf, bufsize);
    }
    return -1;
}

static int _fs_get_size(const char* path) {
    if (File f = FS.open(path, "r")) {
        return f.size();
    }
    return -1;
}

static bool _fs_exists(const char* path) {
    return FS.exists(path);
}

static bool _fs_rename(const char* from, const char* to) {
    return FS.rename(from, to);
}

static bool _fs_unlink(const char* path) {
    return FS.remove(path);
}

static bool _fs_clean_dir(const char* path) {
    Dir dir = FS.openDir(path);
    while (dir.next()) {
#ifdef NVS_USE_SPIFFS
        String p = dir.fileName();
#else
        String p = String(path) + dir.fileName();
#endif
        FS.remove(p.c_str());
        LOG_I("erased %s", p.c_str());
    }
    return true;
}
