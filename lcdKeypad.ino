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
      cook = true;
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
      timeFlag = false;
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
