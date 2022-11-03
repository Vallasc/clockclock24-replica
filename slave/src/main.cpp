#include <Arduino.h>
#include <AccelStepper.h>
#include <Wire.h>

#include "config.h"
#include "board.h"

// Called when the I2C slave is read from
// void requestEvent() {
//   Wire.write("hello ");
// }

// void receiveEvent(int howMany)
// {
//   while(Wire.available()) // loop through all but the last
//   {
//     char c = Wire.read(); // receive byte as a character
//     Serial.print(c);         // print the character
//   }
//   int x = Wire.read();    // receive byte as an integer
//   Serial.println(x);         // print the integer
//   while (Wire.available()) { // peripheral may send less than requested
//     char c = Wire.read(); // receive a byte as character
//     Serial.println(c);         // print the character
//   } 
// }

void setup()
{  
  Serial.begin(115200);
  delay(2000);
  Serial.println("clockclock24 replica by Vallasc");

  board_begin();

  // Wire.begin(i2c_address);
  // Wire.onRequest(requestEvent);
  // Wire.onReceive(receiveEvent);
  // t_clock state = {180, 90, 500, 500, 500, 500, clockwise, clockwise};
  // set_clock1(state);
}

int pos = 275;

void loop()
{
  board_loop();
  if(!clock1_distance_to_go(true, false)){
    delay(1000);
    pos = (pos - 50) % 360;
    pos = pos < 0 ? 360 + pos : pos;
    Serial.println(pos);
    t_clock state = {pos, 0, 500, 500, 500, 500, counterclockwise, counterclockwise};
    set_clock1(state);
  }
}

void setup1()
{  
}

void loop1()
{  
  Serial.println("We we");
}