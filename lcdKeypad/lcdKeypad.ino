#include <Keypad.h>
#include <LiquidCrystal.h>

enum message {welcome, timer, confirm, waitingBoiling, infoDisplay, endCooking} phase;

// LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
LiquidCrystal lcd(23, 25, 27, 29, 31, 33, 35, 37, 39, 41);

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
int temperature= 20;
unsigned long remainingTime;
unsigned long timeToCook;
unsigned long beginTime;
bool timeFlag = false;

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Hello world\n");
  lcd.begin(16,2);
  lcd.print("hello, world!");
  phase = welcome;
  beginTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  readKeypad();
  if (millis() - beginTime >= 1000){
    writeToLCD();
    beginTime = millis();
    remainingTime--;
  }
  if (phase == (endCooking + 1)) {
    phase = welcome;
    timeFlag=false;
  }
}

void readKeypad(){
  char customKey = keypad.getKey();
  
  if (customKey == '#'){
    timeToCook = convertMinToSec(convertToInt(digit[0], digit[1]));    
    Serial.println(digit);
    digit[0], digit[1] = NULL;
    currentDigit = 0;
    phase = phase+1;
  }
  else if (customKey == '*'){
    phase = phase - 1;
  }
  else if (customKey && currentDigit<2 && phase == timer) {
    digit[currentDigit] = customKey;
    currentDigit++;
  }
}

void writeToLCD()
{
  switch(phase){
    case welcome :
      lcd.clear();
      lcd.print("PASTABOT");
      lcd.setCursor(0,1);
      lcd.print("Press # to begin");
      Serial.print("PASTABOT\nPress # to begin\n");
      break;
    case timer :
      lcd.clear();
      lcd.print("Time to cook ?");
      Serial.print("Time to cook ?\n");
      break;
    case confirm :
      lcd.clear();
      lcd.print("Is the time ok?");
      lcd.setCursor(0,1);
      lcd.print(timeToCook);
      lcd.setCursor(2,1);
      lcd.print("min");
      //lcd.print("Confirm");
      Serial.print(digit[1]);
      Serial.print("test\n");
      Serial.print("\n");
      break;
    case waitingBoiling :
      lcd.clear();
      lcd.print("Waiting water to");
      lcd.setCursor(0,1);
      //String temperatureMessage = String ("boil: " + temperature);
      //lcd.print(temperatureMessage);
      lcd.print("boil : ");
      lcd.setCursor(7,1);
      lcd.print(temperature);
      lcd.setCursor(9,1);
      lcd.print(" C");
      Serial.print("test\n");
      break;
    case infoDisplay :
      // Il faudrait déplacer le if suivant dans une fonction plus adaptée
      if (!timeFlag){
        remainingTime = timeToCook;
        timeFlag = true;
      }
      lcd.clear();
      //String remainingTimeMessage = String("time: " + remainingTime);
      //lcd.print(remainingTimeMessage);
      lcd.print("Time:");
      lcd.setCursor(6,0);
      lcd.print(remainingTime/60);
      lcd.setCursor(8,0);
      lcd.print(":");
      lcd.setCursor(10,0);
      lcd.print(remainingTime%60);
      lcd.setCursor(0,1);
      lcd.print("Temperature: ");
      
      break;
    case endCooking :
      lcd.clear();
      lcd.print("Have a ");
      lcd.setCursor(0,1);
      lcd.print("nice meal");
      Serial.print("Have a nice meal\n");
      break;
  }
}

char convertToCharacter(char i) {
  return (i + '0');
}

// convert 2 digit to a single int
int convertToInt(char tensDigit, char unitDigit){
  if (unitDigit == NULL){
    return tensDigit;    
  }
  else{
    return (10*tensDigit + unitDigit);
  }
}

unsigned long convertMinToSec(int minute){
  return 60*minute;
}


