#include <Arduino.h>

enum modes {
    min_distance,
    max_distance,
    clockwise,
    clockwise2,
    clockwise3,
    counterclockwise,
    counterclockwise2,
    counterclockwise3
};

typedef struct clock_state {
    uint16_t angle_h;
    uint16_t angle_m;
    uint16_t speed_h;
    uint16_t speed_m;
    uint16_t accel_h;
    uint16_t accel_m;
    uint8_t mode_h;
    uint8_t mode_m;
} t_clock;

typedef struct half_digit {
    t_clock clock_1;
    t_clock clock_2;
    t_clock clock_3;
    uint8_t i2c_address;
} t_half_digit;