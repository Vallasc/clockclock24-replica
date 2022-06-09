#include <AccelStepper.h>

const int STEPS = 360 * 12;

const int A_STEP = 0; // f(scx)
const int A_DIR = 1; // CW/CCW

const int B_STEP = 2; // f(scx)
const int B_DIR = 3; // CW/CCW

const int RESET = 22;
const int HALL = 15;

// Define a stepper and the pins it will use
AccelStepper stepper1(AccelStepper::DRIVER, A_STEP, A_DIR);
AccelStepper stepper2(AccelStepper::DRIVER, B_STEP, B_DIR);
void setup()
{  
  pinMode(RESET, OUTPUT);
  pinMode(HALL, INPUT_PULLUP);
  
  digitalWrite(RESET, HIGH);
  Serial.begin(9600);
  // Change these to suit your stepper if you want
  stepper1.setMaxSpeed(16000);
  stepper1.setAcceleration(2000);

  stepper2.setMaxSpeed(16000);
  stepper2.setAcceleration(2000);
  
  //stepper.moveTo(STEPS);
  stepper1.moveTo(STEPS);
  stepper2.moveTo(STEPS);
}

bool forward1 = true;
bool forward2 = true;
int position1 = STEPS * 0; // 3/4;
int position2 = STEPS * 1; // 1/4;

void loop()
{
    // If at the end of travel go to the other end
    //if (stepper.distanceToGo() == 0)
    //  stepper.moveTo(-stepper.currentPosition());

    if (stepper1.distanceToGo() == 0) {
      stepper1.moveTo(forward1 ? position1 : position2);
      forward1 = !forward1;
    }

     if (stepper2.distanceToGo() == 0) {
      stepper2.moveTo(forward2 ? position1 : position2);
      forward2 = !forward2;
    }
    
    
    stepper1.run();
    stepper2.run();
    Serial.println(digitalRead(HALL));
}
