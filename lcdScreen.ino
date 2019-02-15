#include <LiquidCrystal.h>

// LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
LiquidCrystal lcd(3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

void setup()
{
  lcd.begin(16,1);
  lcd.print("hello, world!");
}

void loop() {}

void setTimeScreen() {
  lcd.print("Time ?");
}

