#ifndef clock_state_h
#define clock_state_h

#include <Arduino.h>

/***************** Shared *****************/

enum directions
{
  CLOCKWISE,
  CLOCKWISE2,
  CLOCKWISE3,
  COUNTERCLOCKWISE,
  COUNTERCLOCKWISE2,
  COUNTERCLOCKWISE3,
  MIN_DISTANCE,
  MIN_DISTANCE2,
  MIN_DISTANCE3,
  MAX_DISTANCE,
  MAX_DISTANCE2,
  MAX_DISTANCE3,
  ADJUST_LANCET
};

typedef struct clock_state
{
  uint16_t angle_h;
  uint16_t angle_m;
  uint16_t speed_h;
  uint16_t speed_m;
  uint16_t accel_h;
  uint16_t accel_m;
  uint8_t mode_h;
  uint8_t mode_m;
  signed char adjust_h;
  signed char adjust_m;
} t_clock;

typedef struct half_digit
{
  t_clock clocks[3];
  uint32_t change_counter[3];
} t_half_digit;

/***************** Local *****************/

typedef struct clock_state_lite
{
  uint16_t angle_h;
  uint16_t angle_m;
} t_clockl;

typedef struct half_digit_lite
{
  t_clockl clocks[3];
} t_half_digitl;

typedef struct digit
{
  t_half_digitl halfs[2];
} t_digit;

typedef struct full_clock
{
  t_digit digit[4];
} t_full_clock;

#endif