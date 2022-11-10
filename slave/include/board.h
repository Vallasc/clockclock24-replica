#ifndef BOARD_H
#define BOARD_H

#include "clock_accel_stepper.h"
#include "board_config.h"
#include "clock_state.h"

#define INIT_LANCET_ANGLE 270

void board_begin();

void board_loop();

uint8_t get_i2c_address();

bool clock_is_running(int index);

void set_clock(int index, t_clock state);

void adjust_h_lancet(int index, signed char amount);

void adjust_m_lancet(int index, signed char amount);

#endif