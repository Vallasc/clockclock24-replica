#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

static bool _fs_init() {
    return true;
}

static bool _fs_mkdir(const char *path) {
    struct stat statbuf;

    if (stat(path, &statbuf) == 0) {
        if ((statbuf.st_mode & S_IFDIR) != 0) {
            return true;
        } else {
            LOG_E("mkdir failed, file exists %s", path);
            return false;
        }
    } else {
        if (errno != ENOENT) {
            // Error other than file does not exist
            LOG_E("stat filed errno=%d", errno);
            return false;
        }
    }

    // File does not exist (errno == 2)
    if (mkdir(path, 0777) == 0) {
        return true;
    } else {
        LOG_E("mkdir failed errno=%d", errno);
        return false;
    }
}

static bool _fs_verify(const char* path, const void* buf, int bufsize) {
    int fd = open(path, O_RDONLY);
    if (fd >= 0) {
        struct stat st;
        stat(path, &st);
        if (st.st_size == bufsize && bufsize <= 1024) {
            // Check if content is the same
            uint8_t tmp[bufsize];
            if (read(fd, tmp, bufsize) == bufsize) {
                if (!memcmp(buf, tmp, bufsize)) {
                    return true;
                }
            }
        }
    }
    return false;
}

static int _fs_create(const char* path, const void* buf, int bufsize) {
    int fd = open(path, O_WRONLY | O_CREAT);
    if (fd == -1) {
        return -1;
    }
    int len = write(fd, buf, bufsize);
    close(fd);
    return len;
}

static int _fs_read(const char* path, void* buf, int bufsize) {
    int fd = open(path, O_RDONLY);
    if (fd == -1) {
        return -1;
    }
    int len = read(fd, buf, bufsize);
    close(fd);
    return len;
}

static int _fs_get_size(const char* path) {
    struct stat st;
    if (0 == stat(path, &st)) {
        return st.st_size;
    }
    return -1;
}

static bool _fs_exists(const char* path) {
    struct stat st;
    return (0 == stat(path, &st));
}

static bool _fs_rename(const char* from, const char* to) {
    return (0 == rename(from, to));
}

static bool _fs_unlink(const char* path) {
    return (0 == unlink(path));
}

static bool _fs_clean_dir(const char* path) {
    DIR* dir = opendir(path);
    if (!dir) return false;

    struct dirent entry;
    struct dirent *result;

    for (int ret = readdir_r(dir, &entry, &result);
         result != NULL && ret == 0;
         ret = readdir_r(dir, &entry, &result))
    {
        const char* name = entry.d_name;
        if (!strcmp(name, ".") || !strcmp(name, "..")) {
            continue;
        }
        String p = String(path) + name;
        if (0 != unlink(p)) {
            closedir(dir);
            return false;
        } else {
            LOG_I("erased %s", p.c_str());
        }
    }
    closedir(dir);
    return true;
}
