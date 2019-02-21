#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 
char digit[2];
char currentDigit = 0;


Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(9600);

}
  
void loop(){
  char customKey = keypad.getKey();
  
  if (customKey == '#'){
    
    Serial.println(digit);
    digit[0], digit[1] = 0;
    currentDigit = 0;
  }
  else if (customKey && currentDigit<2) {
    digit[currentDigit] = customKey;
    currentDigit++;
  }
}
