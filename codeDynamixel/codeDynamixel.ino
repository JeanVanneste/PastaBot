#include "AX12A.h"

#define DirectionPin   (10u)
#define BaudRate      (500000ul)
#define ID        (10u)

void setup() {
  // put your setup code here, to run once:
  ax12a.begin(BaudRate, DirectionPin, &Serial);
  ax12a.setEndless(ID, ON);
}

void loop() {
  // put your main code here, to run repeatedly:
  turnLeft();
}

void turnLeft(){
  //ax12a.moveSpeed(ID2, pushbee_pos, servo_speed);
  ax12a.turn(ID, LEFT, 500);
  delay(1000);
  ax12a.turn(ID, LEFT, 0);
  delay(1000);
}
