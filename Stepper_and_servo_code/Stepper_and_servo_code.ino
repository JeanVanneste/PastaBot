/*
  This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
  It won't work with v1.x motor shields! Only for the v2's with built in PWM
  control

  For use with the Adafruit Motor Shield v2
  ---->	http://www.adafruit.com/products/1438
*/


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Servo myservo;

// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 and #1 (M3 and M4)
Adafruit_StepperMotor *myMotor1 = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *myMotor2 = AFMS.getStepper(200, 2);

//constants for sensors
const int ButtonSensor = 5;
const int TopSensor = 6;

int ButtonSensorState;
int TopSensorState;



void setup() {
  //stepper motor
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  myMotor1->setSpeed(300);// 10 rpm
  myMotor2->setSpeed(300);// 10 rpm

  //servo motor
  myservo.attach(10);
  Serial.begin(9600);

  // end course sensor
  pinMode( ButtonSensor , INPUT);
  pinMode(TopSensor, INPUT);
}

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
 TopSensorState = digitalRead( TopSensor);  
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

void loop() {
 

//
// pos0();
// delay(1000);
//
//  pos90();
// delay(1000);
// forward1(50);
 //delay(5000);
// 
// backward1(50);
// delay(1000);
// pos180();
// delay(1000);
//forward2(5);
//delay(1000);
//backward2(5);
//delay(1000);

forwardSensor();
 
}
