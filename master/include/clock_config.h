#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <Preferences.h>

enum wireless_modes {
    HOTSPOT, 
    EXT_CONN
};

enum clock_modes {
    LAZY, 
    FUN,
    OFF
};

void begin_config();

void clear_config();

int get_clock_mode();

bool get_sleep_time(int day, int hour);

int get_wireless_mode();

int get_timezone();

char *get_ssid();

char *get_password();

void set_clock_mode(int value);

void set_sleep_time(int day, int hour, bool value);

void save_sleep_time();

void set_wireless_mode(int value);

void set_timezone(int value);

void set_ssid(const char *value);

void set_password(const char *value);

#endif