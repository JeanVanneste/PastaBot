#include <Keypad.h>
#include <LiquidCrystal.h>

enum message {welcome, timer, confirm, infoDisplay} phase;

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

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("Hello world\n");
  lcd.begin(16,2);
  lcd.print("hello, world!");
  phase = welcome;
}

void loop() {
  // put your main code here, to run repeatedly:
  readKeypad();
  writeToLCD();
}

void readKeypad(){
  char customKey = keypad.getKey();
  
  if (customKey == '#'){    
    Serial.println(digit);
    convertToInt(digit[0], digit[1]);
    digit[0], digit[1] = 0;
    currentDigit = 0;
    phase = phase+1;
  }
  else if (customKey == '*'){
    phase = phase - 1;
  }
  else if (customKey && currentDigit<2) {
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
      //String displayedMessage = String("Is " + digit[0] + digit[1] + " min is OK ?");
      //lcd.print(displayedMessage);
      Serial.print(digit[1]);
      Serial.print("\n");
      break;
  }
}

char convertToCharacter(char i) {
  return (i + '0');
}

// convert 2 digit to a single int
// TODO check if only one number is pressed
int convertToInt(char tensDigit, char unitDigit){
  return (10*tensDigit + unitDigit);
}
