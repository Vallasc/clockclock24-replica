#ifndef clock_manager_h
#define clock_manager_h

#include "clock_state.h"
#include "i2c.h"
#include "digit.h"
#include "clock_config.h"

void set_mode(int mode);

void send_half_digit(int address, t_half_digit half_digit);

// 0 <= index < 4
void send_digit(int index, t_digit digit);

void send_clock(t_full_clock full_clock);

t_half_digit get_full_half_digit(t_half_digitl lite_digit);

void set_clock(t_full_clock clock_state);

void set_clock_time(int h, int m);

void adjust_lancet(int clock_index, int h_amount, int m_amount);

#endif