#ifndef clock_manager_h
#define clock_manager_h

#include "clock_state.h"
#include "i2c.h"
#include "digit.h"
#include "clock_config.h"

/** 
 * Returns current direction
 * @return direction
*/
int get_direction();

/** 
 * Returns current speed
 * @return speed
*/
int get_speed();

/** 
 * Returns current acceleration
 * @return acceleration
*/
int get_acceleration();

/** 
 * Sets current direction
 * @param value     direction
*/
void set_direction(int direction);

/** 
 * Sets current speed
 * @param value     speed
*/
void set_speed(int value);

/** 
 * Sets current acceleration
 * @param value     acceleration
*/
void set_acceleration(int value);

/** 
 * Sends half digit to the specified board
 * @param index         board index (0 <= index < 8)
 * @param half_digit    digit to send
*/
void send_half_digit(int index, t_half_digit half_digit);

/** 
 * Sends a digit to the specified boards
 * @param index         board index (0 <= index < 8)
 * @param half_digit    digit to send
*/
void send_digit(int index, t_digit digit);

/** 
 * Sends the full clock configuration to boards
 * @param full_clock    clock configuration
*/
void send_clock(t_full_clock full_clock);

/** 
 * Converts t_half_digitl to t_half_digit
 * @param lite_digit    t_half_digitl
 * @return t_half_digit
*/
t_half_digit get_full_half_digit(t_half_digitl lite_digit);

/** 
 * Sends the full clock configuration to boards and increments
 * the state counter
 * @param clock_state   clock state
*/
void set_clock(t_full_clock clock_state);

/** 
 * Sends a digit to the specified boards and increments
 * the state counter
 * @param index     digit index (0 <= index < 4)
 * @param digit     digit value
*/
void set_digit(int index, t_digit digit);

/** 
 * Sends a half digit to the specified board and increments
 * the state counter
 * @param index     digit index (0 <= index < 8)
 * @param half      hlaf digit value
*/
void set_half_digit(int index, t_half_digitl half);

/** 
 * Sets the specified time on the clock
 * @param h     hour
 * @param m     minute
*/
void set_clock_time(int h, int m);

/** 
 * Returns a full clock state from time
 * @param h     hour
 * @param m     minute
 * @return full clock state
*/
t_full_clock get_clock_state_from_time(int h, int m);

/** 
 * @param clock_index   single clock index (0 <= index < 24)
 * @param h_amount      hours hand degree of adjustment
 * @param m_amount      minutes hand degree of adjustment
*/
void adjust_hands(int clock_index, int h_amount, int m_amount);

#endif