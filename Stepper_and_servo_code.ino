/*
  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
  It won't work with v1.x motor shields! Only for the v2's with built in PWM
  control

  For use with the Adafruit Motor Shield v2
  ---->  http://www.adafruit.com/products/1438
*/

// stepper motor
//int backward1( int angle){
//int i;
//int n;
//i=n=0;
//while ( i < angle){
//  myMotor1 -> step(100, BACKWARD , DOUBLE);
//  i = i+1;
//  }
//}

//int forward1(int angle){
//int i;
//int n;
//i=n=0;
//while ( i < angle){
//  myMotor1 -> step(100, FORWARD, DOUBLE);
//  i = i+1;
//  }
//}

int backward2( int angle){
int i;
int n;
i=n=0;
while ( i < angle){
  myMotor2 -> step(100, BACKWARD , DOUBLE);
  i = i+1;
  }
}

int forward2(int angle){
int i;
int n;
i=n=0;
while ( i < angle){
  myMotor2 -> step(100, FORWARD, DOUBLE);
  i = i+1;
  }
}


//servo motor
// servo à la position 0°
void pos0() {
  myservo.write(0);
  delay(1000);
  Serial.println(myservo.read());
  }
  
//servo à 90°
void pos90(){
  myservo.write(90);
  delay(1000);
  Serial.println(myservo.read());
}

//servo à 180°
void pos180(){
  myservo.write(180);
  delay(1000);
  Serial.println(myservo.read());
}

// stepper motor + sensor
void backwardSensor( ){
  int TopSensorState = digitalRead( TopSensor);  
  while ( ButtonSensorState == HIGH){
    myMotor1 -> step(100, BACKWARD , DOUBLE);
    TopSensorState = digitalRead( TopSensor);
  }
}

void forwardSensor( ){
  ButtonSensorState = digitalRead( ButtonSensor);
  while ( ButtonSensorState == HIGH){
    myMotor1 -> step(100, FORWARD , DOUBLE);
    Serial.println(ButtonSensorState);
    ButtonSensorState = digitalRead( ButtonSensor);
  }
}
