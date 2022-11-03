#include <AccelStepper.h>
#include "config.h"
#include "clock_state.h"

// Define a stepper and the pins it will use
AccelStepper s_A (AccelStepper::DRIVER, A_STEP, A_DIR);
AccelStepper s_B (AccelStepper::DRIVER, B_STEP, B_DIR);

AccelStepper s_C (AccelStepper::DRIVER, C_STEP, C_DIR);
AccelStepper s_D (AccelStepper::DRIVER, D_STEP, D_DIR);

AccelStepper s_E (AccelStepper::DRIVER, E_STEP, E_DIR);
AccelStepper s_F (AccelStepper::DRIVER, F_STEP, F_DIR);

uint8_t i2c_address;

t_clock clock1 = {0, 0, 500, 500, 500, 500, clockwise, clockwise};

void board_begin()
{
  // Reset motor controllers
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);

  // s_E.setCurrentPosition(275 * STEPS /360);
  // s_F.setCurrentPosition(275 * STEPS /360);

  s_A.setMaxSteps(STEPS);
  s_B.setMaxSteps(STEPS);
  s_C.setMaxSteps(STEPS);
  s_D.setMaxSteps(STEPS);
  s_E.setMaxSteps(STEPS);
  s_F.setMaxSteps(STEPS);

  //s_A.setCurrentPosition(STEPS*);
  // s_B.setMaxSteps(STEPS);
  // s_C.setMaxSteps(STEPS);
  // s_D.setMaxSteps(STEPS);
  // s_E.setMaxSteps(STEPS);
  // s_F.setMaxSteps(STEPS);

  s_A.setMaxSpeed(16000);
  s_A.setAcceleration(2000);
  s_B.setMaxSpeed(16000);
  s_B.setAcceleration(2000);

  s_C.setMaxSpeed(16000);
  s_C.setAcceleration(2000);
  s_D.setMaxSpeed(16000);
  s_D.setAcceleration(2000);

  pinMode(ADDR_1, INPUT_PULLUP);
  pinMode(ADDR_2, INPUT_PULLUP);
  pinMode(ADDR_3, INPUT_PULLUP);
  pinMode(ADDR_4, INPUT_PULLUP);
  i2c_address = !digitalRead(ADDR_1) + (!digitalRead(ADDR_2) << 1) + 
            (!digitalRead(ADDR_3) << 2) + (!digitalRead(ADDR_4) << 3);
}

void board_loop()
{
  s_A.runDirection();
  s_B.runDirection();
  s_C.runDirection();
  s_D.runDirection();
  s_E.runDirection();
  s_F.runDirection();
}

uint8_t get_i2c_address()
{
  return i2c_address;
}

int clock1_distance_to_go(boolean hour, boolean min)
{
  return (hour ? s_F.distanceToGo() : 0) + (min ? s_E.distanceToGo() : 0);
}

void set_clock1(t_clock state)
{
  s_F.setMaxSpeed(state.speed_h);
  s_F.setAcceleration(state.accel_h);
  s_F.moveToDirection(state.angle_h * STEPS /360, state.mode_h == clockwise);

  s_E.setMaxSpeed(state.speed_m);
  s_E.setAcceleration(state.accel_m);
  s_E.moveToDirection(state.angle_m * STEPS /360, state.mode_m == clockwise);
  clock1 = state;
}