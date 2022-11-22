#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include <Preferences.h>

/** 
 * Clock connection's modes
 */
enum wireless_modes
{
  HOTSPOT,
  EXT_CONN
};

/** 
 * Clock animation's modes
 */
enum clock_modes
{
  LAZY,
  FUN,
  WAVES,
  OFF
};

/**
 * Load configuration from the EEPROM
 */
void begin_config();

/**
 * Clear EEPROM configuration
 */
void clear_config();

/**
 * Closes the preferencies object
 */
void end_config();

/**
 * Get current clock mode
 */
int get_clock_mode();

/**
 * Gets current sleep time at a given day and hour
 * @param day   day of the week
 * @param hour  hour of the day
 */
bool get_sleep_time(int day, int hour);

/**
 * Gets current connection mode
 */
int get_connection_mode();

/**
 * Gets current time zone based on UTC offset
 */
int get_timezone();

/**
 * Gets current SSID
 */
char *get_ssid();

/**
 * Gets current password
 */
char *get_password();

/**
 * Sets clock mode
 * @param value   mode value of type clock_modes
 */
void set_clock_mode(int value);

/**
 *  Sets current sleep time at a given day and hour
 * @param day   day of the week
 * @param hour  hour of the day
 * @param value true if clock is  disabled, false otherwise
 */
void set_sleep_time(int day, int hour, bool value);

/**
 *  Saves sleep time array on EEPROM
 */
void save_sleep_time();

/**
 *  Sets connection mode
 * @param value   mode value of type wireless_modes
 */
void set_connection_mode(int value);

/**
 *  Sets the time zone
 * @param value   time zone based on UTC offset
 */
void set_timezone(int value);

/**
 *  Sets SSID value
 * @param value   SSID string
 */
void set_ssid(const char *value);

/**
 *  Sets password value
 * @param value   password string
 */
void set_password(const char *value);

#endif