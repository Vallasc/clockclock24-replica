#ifndef CLOCK_STATE_H
#define CLOCK_STATE_H

enum directions {
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
    ADJUST_HAND
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
    signed char adjust_h;
    signed char adjust_m;
} t_clock;

typedef struct half_digit {
    t_clock clocks[3];
    uint32_t change_counter[3];
} t_half_digit;

#endif