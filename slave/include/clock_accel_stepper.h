#ifndef CLOCK_ACCEL_STEPPER_H
#define CLOCK_ACCEL_STEPPER_H

#include <AccelStepper.h>
#include "clock_state.h"

/**
 * Subclass specialized on clock movements.
*/
class ClockAccelStepper : public AccelStepper
{
  private:
    int _current_angle;
    int _max_steps;
    bool _reverse;

  public:
    explicit ClockAccelStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5, bool enable = true);

    /**
     * Set clock hand to a specified angle.
     * @param angle   (0 <= angle < 360)
    */
    void setHandAngle(int angle);

    /**
     * Reverse clock direction.
     * @param reverse
    */
    void setReverse(bool reverse);

    /**
     * Set one revolution motor steps.
     * @param steps   number of steps
    */
    void setMaxMotorSteps(int steps);

    /**
     * Calculate the delta angle between current_angle and target_angle
     * using a clockwise direction
     * @param current_angle   current angle
     * @param target_angle    target angle
    */
    int calcAngleClockwise(int current_angle, int target_angle);

    /**
     * Calculate the delta angle between current_angle and target_angle
     * using a clockwise direction
     * @param current_angle   current angle
     * @param target_angle    target angle
    */
    int calcAngleCounterclockwise(int current_angle, int target_angle);

    /**
     * Moves clock to a specified angle and direction.
     * @param angle       angle to go
     * @param direction   direction
    */
    void moveToAngle(int angle, int direction);
};

#endif