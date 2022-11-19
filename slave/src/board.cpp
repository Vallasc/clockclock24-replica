#include "board.h"

// Define a stepper and the pins it will use
ClockAccelStepper _motors[6] = {
  ClockAccelStepper(ClockAccelStepper::DRIVER, F_STEP, F_DIR), // 0 -> h clock 0
  ClockAccelStepper(ClockAccelStepper::DRIVER, E_STEP, E_DIR), // 1 -> m clock 0
  ClockAccelStepper(ClockAccelStepper::DRIVER, D_STEP, D_DIR), // 2 -> h clock 1
  ClockAccelStepper(ClockAccelStepper::DRIVER, C_STEP, C_DIR), // 3 -> m clock 1
  ClockAccelStepper(ClockAccelStepper::DRIVER, B_STEP, B_DIR), // 4 -> h clock 2
  ClockAccelStepper(ClockAccelStepper::DRIVER, A_STEP, A_DIR)  // 5 -> m clock 2
};

uint8_t _i2c_address = 0;

static int sanitize_angle(int angle)
{
  angle = angle % 360;
  return angle < 0 ? 360 + angle : angle;
}

void board_begin()
{
  // Reset motor controllers
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);

  // Init motors
  for(int i = 0; i < 6; i++)
  {
    if(i % 2 == 1)
      _motors[i].setReverse(true);
    _motors[i].setMaxMotorSteps(STEPS);
    _motors[i].setHandAngle(INIT_HANDS_ANGLE);
    _motors[i].setMinPulseWidth(0);
  }

  pinMode(ADDR_1, INPUT_PULLUP);
  pinMode(ADDR_2, INPUT_PULLUP);
  pinMode(ADDR_3, INPUT_PULLUP);
  pinMode(ADDR_4, INPUT_PULLUP);
  _i2c_address = !digitalRead(ADDR_1) + 
               (!digitalRead(ADDR_2) << 1) + 
               (!digitalRead(ADDR_3) << 2) + 
               (!digitalRead(ADDR_4) << 3);
}

void board_loop()
{
  for(int i = 0; i < 6; i++)
    _motors[i].run();
}

uint8_t get_i2c_address()
{
  return _i2c_address;
}

bool clock_is_running(int index)
{
  if( index < 0 || index > 2)
    return false;

  return _motors[index*2].distanceToGo() != 0 || 
         _motors[index*2 + 1].distanceToGo();
}

void set_clock(int index, t_clock state)
{
  int angle_h = sanitize_angle(state.angle_h + state.adjust_h);
  _motors[index*2].setMaxSpeed(state.speed_h);
  _motors[index*2].setAcceleration(state.accel_h);
  _motors[index*2].moveToAngle(angle_h, state.mode_h);

  int angle_m = sanitize_angle(state.angle_m + state.adjust_m);
  _motors[index*2 + 1].setMaxSpeed(state.speed_m);
  _motors[index*2 + 1].setAcceleration(state.accel_m);
  _motors[index*2 + 1].moveToAngle(angle_m, state.mode_m);
}

void adjust_h_hand(int index, signed char amount)
{
  int steps = amount * STEPS / 360;
  _motors[index*2 + 1].move(steps);
  _motors[index*2 + 1].runToPosition();
}

void adjust_m_hand(int index, signed char amount)
{
  int steps = amount * STEPS / 360;
  _motors[index*2].move(-steps);
  _motors[index*2].runToPosition();
}