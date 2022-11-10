# Preferences

[![Arduino Library Manager](https://img.shields.io/static/v1?label=Arduino&message=v2.0.0&logo=arduino&logoColor=white&color=blue)](https://www.ardu-badge.com/Preferences)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/vshymanskyy/library/Preferences.svg)](https://registry.platformio.org/packages/libraries/vshymanskyy/Preferences) 

Preferences library for **ESP8266** and **Particle Gen3** devices. **ESP32**-compatible API.

Available from: [`Arduino Library Manager`](https://www.arduino.cc/reference/en/libraries/preferences), [`PlatformIO`](https://registry.platformio.org/libraries/vshymanskyy/Preferences), [`Particle Build`](https://build.particle.io/libs/Preferences)

[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/banner-direct-single.svg)](https://stand-with-ukraine.pp.ua)

## How does it work?

```cpp
#include <Preferences.h>
Preferences prefs;

void setup() {
  Serial.begin(115200);
  prefs.begin("my-app");

  int counter = prefs.getInt("counter", 1); // default to 1
  Serial.printf("Reboot count: %d\n", counter);
  counter++;
  prefs.putInt("counter", counter);
}

void loop() {}
```

Preferences are stored in the internal flash filesystem in a bunch of `/nvs/{namespace}/{property}` files.  
Filesystem should handle flash wearing, bad sectors and atomic `rename` file operation.  
`LittleFS` handles all that, so this is the default FS driver for ESP8266.  
Particle Gen3 devices also operate on `LittleFS` filesystem.

## Supported devices

- Arduino ESP8266 with LittleFS or SPIFFS
- Particle Argon, Boron, Xenon, Tracker, BSOM

Can be easily adjusted for any device with a reliable and POSIX-compatible filesystem

## API

Check out ESP32 [Preferences library](https://espressif-docs.readthedocs-hosted.com/projects/arduino-esp32/en/latest/api/preferences.html) API.
Differences:
- `partition_label` argument is not supported in `begin()`
- `getType()` and `freeEntries()` methods are not supported (returning dummy values)
