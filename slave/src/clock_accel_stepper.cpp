#include "clock_accel_stepper.h"

ClockAccelStepper::ClockAccelStepper(uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, bool enable)
    : AccelStepper(interface, pin1, pin2, pin3, pin4, enable)
{
  _current_angle = 0;
  _reverse = false;
}

void ClockAccelStepper::setLancetAngle(int angle)
{
  _current_angle = angle;
}

void ClockAccelStepper::setReverse(bool reverse)
{
  _reverse = reverse;
}

void ClockAccelStepper::setMaxMotorSteps(int steps)
{
  _max_steps = steps;
}

int ClockAccelStepper::calcAngleClockwise(int current_angle, int target_angle)
{
  int delta = (target_angle - current_angle) % 360;
  return (delta <= 0) ? -delta : 360 - delta;
}

int ClockAccelStepper::calcAngleCounterclockwise(int current_angle, int target_angle)
{
  int delta = (target_angle - current_angle) % 360;
  return (delta < 0) ? 360 + delta : delta;
}

void ClockAccelStepper::moveToAngle(int angle, int direction)
{
  int multiplier = 1;
  int delta;

  if (direction <= CLOCKWISE3) // CLOCKWISE
  {
    delta = calcAngleClockwise(_current_angle, angle);
    multiplier = direction;
  }
  else if (direction <= COUNTERCLOCKWISE3) // COUNTERCLOCKWISE
  {
    delta = calcAngleCounterclockwise(_current_angle, angle);
    multiplier = direction - 3;
  }
  else if (direction <= MIN_DISTANCE3) // MIN_DISTANCE
  {
    multiplier = direction - 6;
    int delta1 = calcAngleClockwise(_current_angle, angle);
    int delta2 = calcAngleCounterclockwise(_current_angle, angle);
    direction = delta1 < delta2 ? CLOCKWISE : COUNTERCLOCKWISE; // if == COUNTERCLOCKWISE
    delta = delta1 < delta2 ? delta1 : delta2;
  }
  else if (direction <= MAX_DISTANCE3)
  {
    multiplier = direction - 9;
    int delta1 = calcAngleClockwise(_current_angle, angle);
    int delta2 = calcAngleCounterclockwise(_current_angle, angle);
    direction = delta1 > delta2 ? CLOCKWISE : COUNTERCLOCKWISE; // if == COUNTERCLOCKWISE
    delta = delta1 > delta2 ? delta1 : delta2;
  }

  _current_angle = angle;
  int steps = delta * _max_steps / 360;

  if (direction <= CLOCKWISE3) // CLOCKWISE
    steps = steps + (_max_steps * multiplier);
  else if (direction <= COUNTERCLOCKWISE3) // COUNTERCLOCKWISE
    steps = (steps + (_max_steps * multiplier)) * -1;

  move(steps * (_reverse ? -1 : 1));
}