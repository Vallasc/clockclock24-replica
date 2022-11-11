#ifndef digit_h
#define digit_h

#include <Arduino.h>
#include "clock_state.h"

/**
 * Digits
 * structure: {
 * h0, m0,
 * h1, m1,
 * ...
 * h5, m5
 * }
*/

const t_digit digit_0 = {
  270, 0,
  270, 90,
  0, 90,
  270, 180,
  270, 90,
  180, 90
};

const t_digit digit_1 = {
  225, 225,
  225, 225,
  225, 225,
  270, 270,
  270, 90,
  90, 90
};

const t_digit digit_2 = {
  0, 0,
  270, 0,
  90, 0,
  180, 270,
  90, 180,
  180, 180
};

const t_digit digit_3 = {
  0, 0,
  0, 0,
  0, 0,
  180, 270,
  180, 90,
  180, 90
};

const t_digit digit_4 = {
  270, 270,
  90, 0,
  225, 225,
  270, 270,
  270, 90,
  90, 90
};

const t_digit digit_5 = {
  270, 0,
  90, 0,
  0, 0,
  180, 180,
  270, 180,
  90, 180
};

const t_digit digit_6 = {
  270, 0,
  270, 90,
  90, 0,
  180, 180,
  270, 180,
  90, 180
};

const t_digit digit_7 = {
  0, 0,
  225, 225,
  225, 225,
  270, 180,
  270, 90,
  90, 90
};

const t_digit digit_8 = {
  270, 0,
  90, 0,
  90, 0,
  270, 180,
  90, 180,
  90, 180
};

const t_digit digit_9 = {
  270, 0,
  0, 90,
  0, 0,
  270, 180,
  270, 90,
  90, 180
};

const t_digit digit_null = {
  270, 270,
  270, 270,
  270, 270,
  270, 270,
  270, 270,
  270, 270
};

const t_digit digit_I = {
  270, 90,
  270, 90,
  270, 90,
  270, 90,
  270, 90,
  270, 90
};

const t_digit digit_fun = {
  225, 45,
  225, 45,
  225, 45,
  225, 45,
  225, 45,
  225, 45,
};

const t_full_clock d_stop = {digit_null, digit_null, digit_null, digit_null};

const t_full_clock d_fun = {digit_fun, digit_fun, digit_fun, digit_fun};

const t_full_clock d_IIII = {digit_I, digit_I, digit_I, digit_I};

#endif