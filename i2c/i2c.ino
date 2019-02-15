#include <Wire.h>

#define LCD_ADDRESS 0x78 // SA = [0,0]

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.beginTransmission(LCD_ADDRESS);
  Wire.write(0x0C); // display on
  Wire.endTransmission();
}

void loop() {
  // put your main code here, to run repeatedly:  
  Wire.beginTransmission(LCD_ADDRESS);
  Wire.write(0x31);
  Wire.endTransmission();
}
