#include <SwitecX12.h>

const int STEPS = 360 * 12;
const int A_STEP = 4; // f(scx)
const int A_DIR = 2; // CW/CCW
const int RESET = 3;

//const int STEPS = 360 * 12;
//const int A_STEP = 8;
//const int A_DIR = 9;
//const int RESET = 10;

SwitecX12 motor1(STEPS, A_STEP, A_DIR);

SwitecX12 motor2(STEPS, 5, 6);
SwitecX12 motor3(STEPS, 7, 8);
SwitecX12 motor4(STEPS, 9, 10);

void setup() {
  pinMode(RESET, OUTPUT);
  digitalWrite(RESET, HIGH);
  //delay(200);
  //digitalWrite(RESET, LOW);
  Serial.begin(9600);
  motor1.zero();
  //motor1.setPosition(STEPS);

  /*motor2.zero();
  motor2.setPosition(STEPS/2);
  motor3.zero();
  motor3.setPosition(STEPS/2);
  motor4.zero();
  motor4.setPosition(STEPS/2);*/
}

bool forward = true;
int position1 = STEPS * 0; // 3/4;
int position2 = STEPS * 1; // 1/4;

void loop() {
  if (motor1.stopped) {
    Serial.println("Stopped");
    delay(1000);
    motor1.setPosition(forward ? position1 : position2);
    forward = !forward;
  }
  
  motor1.update();
  //motor2.update();
  //motor3.update();
  //motor4.update();

  delayMicroseconds(60); // for 50Mhz
}
