
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#include "AX12A.h"

#define DirectionPin   (10u)
#define BaudRate      (500000ul)
#define ID        (10u)

//lcd
enum message {welcome, timer, confirm, waitingBoiling, infoDisplay, endCooking} phase;

// LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
LiquidCrystal lcd(23, 25, 27, 29, 31, 33, 35, 37, 39, 41);

//keypad
const byte ROWS = 4; 
const byte COLS = 4; 

const char hexaKeys[ROWS][COLS] = {
  {1, 2, 3, 'A'},
  {4, 5, 6, 'B'},
  {7, 8, 9, 'C'},
  {'*', 0, '#', 'D'}
};

byte rowPins[ROWS] = {36, 34, 32, 30}; 
byte colPins[COLS] = {28, 26, 24, 22}; 
char digit[2];
char currentDigit = 0;
float temperature= 0;
int tempPin = A10; 
unsigned long remainingTime;
unsigned long timeToCook;
unsigned long beginTime;
bool timeFlag = false;

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

enum State{wait, fillPasta, fillWater, fillSalt, heatWater, turnToPot, inPot, cookPasta, outPot, turnToPlate, serve, emptyWater, comeBack}state;

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// for mqtt
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(172, 17, 4, 44);
// broker.hivemq.com 18.184.104.180
IPAddress server(18, 184, 104, 180);

const char* inTopic = "ecam/pastaBot/cookTime/";
const char* outTopic = "ecam/pastaBot/response/";

int tim;
bool cook = false;
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

Servo saltDispenser;

//for the valves
const double HalfEmptyingTime = 92;//*250
int solenoidPin = 4;    // pin for solenoid filling
int solenoidEmptyWater = 6; // pin for solenoid emptying
const double HalfFillingTime = 107;//*250

//for the motors
#include <Wire.h>
#include <Adafruit_MotorShield.h>

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
const int TopSensor = 7;

int ButtonSensorState;

const int platePin = 53;

void setup() {
  // pasta
  state = fillSalt;
  ax12a.begin(BaudRate, DirectionPin, &Serial);
  ax12a.setEndless(ID, ON);
  
  // salt
  saltDispenser.attach(9);

  //mqtt
  Serial.begin(500000);
  Ethernet.begin(mac, ip);
  if (client.connect("arduinoClient")) {
    Serial.println("connected at the first try");
    client.subscribe(inTopic);
  }

  //valves
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
  pinMode(solenoidEmptyWater, OUTPUT);
  pinMode(platePin, OUTPUT);
  
  digitalWrite(solenoidPin, LOW);
  digitalWrite(solenoidEmptyWater, LOW);
  digitalWrite(platePin, LOW);

  //motors
  Serial.println("Stepper test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  myMotor1->setSpeed(300);// 10 rpm
  myMotor2->setSpeed(300);// 10 rpm

  //servo motor
  myservo.attach(10);
  // end course sensor
  pinMode(ButtonSensor , INPUT);
  pinMode(TopSensor, INPUT);

  //lcd
  lcd.begin(16,2);
  lcd.print("hello, pasta !!");
  phase = welcome;
  beginTime = millis();

  //temperature
  
}

void loop() {
  if (millis() - beginTime >= 1000){
              writeToLCD();
              beginTime = millis();
              remainingTime--;
            }
            if (phase == (endCooking + 1)) {
              phase = welcome;
              timeFlag=false;
            }
    switch (state) {
        case wait:
            Serial.println("State wait");
            // statements
            
            //wait change on tim
            //by mqtt
            client.loop();            
            //by the pad
            
            if (cook == true){
              state = fillPasta;
              break;
            }
            else{
              readKeypad();
            }
            break;
        case fillPasta:
            Serial.println("State fill pasta");
            dispensePasta();
            state = fillWater;
            break;
        case fillWater:
            Serial.println("State fill water");
            FillWater();
            state = fillSalt;   
            break;
        case fillSalt:
            Serial.println("State fill salt");
            dispenseSalt();
            //state = turnToPot;
            break;
        case turnToPot:
        //marche pas
            Serial.println("State turn to pot");
            // statements
            pos90();
            state = heatWater;
            phase = waitingBoiling;
            break;
        case heatWater:
            Serial.println("State heat");
            // statements
            digitalWrite(platePin, HIGH);
            //if ((analogRead(tempPin)/1023.0)*0.5 == 3.30)
            //{
              //digitalWrite(platePin, LOW);
              state = inPot;
            //}
            break;

        case inPot:
            Serial.println("State inPot");
            // statements
            forwardSensor();
            phase = infoDisplay;
            state = cookPasta;
            break;
        case cookPasta:
            Serial.println("State cook");
            temperature = (analogRead(tempPin)/1023.0)*0.5;
            // statements
            if (temperature >= 3.20)
            {
              digitalWrite(platePin, LOW);
            }
            else if(temperature <= 3.20)
            {
              digitalWrite(platePin, HIGH);
            }
            if (remainingTime <= 0)
            {
              digitalWrite(platePin, LOW);
              phase = endCooking;
              state = outPot;
            }
            break;
        case outPot:
            Serial.println("State outpot");
            // statements
            forward2(10);
            backward2(20);
            forward2(10);
            backwardSensor();
            state = turnToPlate;
            break;
        case turnToPlate:
            Serial.println("State turn plate");
            // statements
            pos180();
            state = serve;
            break;
        case serve:
            Serial.println("State serve");
            // statements
            forward2(180);
            state = emptyWater;
            break;
        case emptyWater:
            Serial.println("State empty water");
            // statements
            EmptyWater();
            state = comeBack;
            break;
        case comeBack:
            Serial.println("State turnback");
            // statements
            pos0();
            state = wait;
            break;
        default:
        state = wait;
        // statements
}

}
