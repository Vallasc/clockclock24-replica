#include <Arduino.h>
#include <AccelStepper.h>
//#include <Wire.h>

#define STEPS (360 * 12)

#define A_STEP 0 // f(scx)
#define A_DIR 1 // CW/CCW
#define B_STEP 2 // f(scx)
#define B_DIR 3 // CW/CCW

#define C_STEP 26 // f(scx)
#define C_DIR 27 // CW/CCW
#define D_STEP 6 // f(scx)
#define D_DIR 7 // CW/CCW

#define E_STEP 8 // f(scx)
#define E_DIR 9 // CW/CCW
#define F_STEP 10 // f(scx)
#define F_DIR 11 // CW/CCW

#define ADDR_1 18 // f(scx)
#define ADDR_2 19 // CW/CCW
#define ADDR_3 20 // f(scx)
#define ADDR_4 21 // CW/CCW

#define RESET 22
#define HALL 15

byte address;

// Define a stepper and the pins it will use
AccelStepper s_A (AccelStepper::DRIVER, A_STEP, A_DIR);
AccelStepper s_B (AccelStepper::DRIVER, B_STEP, B_DIR);
bool f_A = true;
bool f_B = true;

AccelStepper s_C (AccelStepper::DRIVER, C_STEP, C_DIR);
AccelStepper s_D (AccelStepper::DRIVER, D_STEP, D_DIR);
bool f_C = true;
bool f_D = true;

AccelStepper s_E (AccelStepper::DRIVER, E_STEP, E_DIR);
AccelStepper s_F (AccelStepper::DRIVER, F_STEP, F_DIR);
bool f_E = true;
bool f_F = true;

// Called when the I2C slave is read from
void req() {
  static int ctr = 765;
  char buff[7];
  // Return a simple incrementing hex value
  sprintf(buff, "%06X", (ctr++) % 65535);
  //Wire1.write(buff, 6);
}

void setup()
{  
  Serial.begin(115200);
  Serial.println("clockclock24 replica by Vallasc");

  // Reset motor controllers
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);
  
  s_A.setMaxSpeed(16000);
  s_A.setAcceleration(2000);
  s_B.setMaxSpeed(16000);
  s_B.setAcceleration(2000);

  s_C.setMaxSpeed(16000);
  s_C.setAcceleration(2000);
  s_D.setMaxSpeed(16000);
  s_D.setAcceleration(2000);

  s_E.setMaxSpeed(16000);
  s_E.setAcceleration(2000);
  s_F.setMaxSpeed(16000);
  s_F.setAcceleration(2000);
  
  //stepper.moveTo(STEPS);
  //stepper1.moveTo(STEPS);
  //stepper2.moveTo(STEPS);

  // Get i2c address from switches
  pinMode(ADDR_1, INPUT_PULLUP);
  pinMode(ADDR_2, INPUT_PULLUP);
  pinMode(ADDR_3, INPUT_PULLUP);
  pinMode(ADDR_4, INPUT_PULLUP);
  Serial.println(digitalRead(ADDR_1));
  Serial.println(digitalRead(ADDR_2));
  Serial.println(digitalRead(ADDR_3));
  Serial.println(digitalRead(ADDR_4));
  address = 3;
  //Wire.setSDA(4);
  //Wire.setSCL(5);
  //Wire.begin();
}

int pos1 = STEPS * 0; // 3/4;
int pos2 = STEPS * 1; // 1/4;

void loop()
{
  Serial.println(!digitalRead(ADDR_1));
  Serial.println(!digitalRead(ADDR_2));
  Serial.println(!digitalRead(ADDR_3));
  Serial.println(!digitalRead(ADDR_4));
  Serial.println();
    // If at the end of travel go to the other end
    //if (stepper.distanceToGo() == 0)
    //  stepper.moveTo(-stepper.currentPosition());

    if (s_A.distanceToGo() == 0) {
      s_A.moveTo(f_A ? pos1 : pos2);
      f_A = !f_A;
    }

    if (s_B.distanceToGo() == 0) {
      s_B.moveTo(f_B ? pos1 : pos2);
      f_B = !f_B;
    }

    if (s_C.distanceToGo() == 0) {
      s_C.moveTo(f_C ? pos1 : pos2);
      f_C = !f_C;
    }

    
    if (s_D.distanceToGo() == 0) {
      s_D.moveTo(f_D ? pos1 : pos2);
      f_D = !f_D;
    }

    if (s_E.distanceToGo() == 0) {
      s_E.moveTo(f_E ? pos1 : pos2);
      f_E = !f_E;
    }

    if (s_F.distanceToGo() == 0) {
      s_F.moveTo(f_F ? pos1 : pos2);
      f_F = !f_F;
    }
    
    s_A.run();
    s_B.run();
    s_C.run();
    s_D.run();
    s_E.run();
    s_F.run();
    
    //Serial.println(digitalRead(HALL));
}
