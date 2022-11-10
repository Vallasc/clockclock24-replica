#ifndef CLOCK_ACCEL_STEPPER_H
#define CLOCK_ACCEL_STEPPER_H

#include <AccelStepper.h>
#include "clock_state.h"

class ClockAccelStepper : public AccelStepper
{
  private:
    int _current_angle;
    int _max_steps;
    bool _reverse;

  public:
    explicit ClockAccelStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);

    void setLancetAngle(int angle);

    void setReverse(bool reverse);

    void setMaxMotorSteps(int steps);

    int calcAngleClockwise(int current_angle, int target_angle);

    int calcAngleCounterclockwise(int current_angle, int target_angle);

    void moveToAngle(int angle, int direction);
};

#endif