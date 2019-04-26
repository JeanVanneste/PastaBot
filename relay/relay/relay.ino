#define RELAY_PIN 7

void setup() {
  Serial.begin(9600);
  Serial.print("Hello world!\n");

  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int temperature = 0;
  bool increasingTemperature = true;
  
  temperature = getTemperature(temperature);
  changeRelayState(temperature, increasingTemperature);
}

/*
int getTemperature(int temperature){
  if (Serial.available() > 0) {
    char n1 = convertToNumber(Serial.read());
    char n2 = convertToNumber(Serial.read());
    char n3 = convertToNumber(Serial.read());
    convertToInt(n1, n2, n3);    
    Serial.print(temperature);
    Serial.print("\n");
  }
  return temperature;
}
*/


int getTemperature(int temperature){
  
}

void changeRelayState(int temperature, bool increasingTemperature){
  if (increasingTemperature) {
    if (temperature > 100){
      increasingTemperature = false;
    }
    digitalWrite(RELAY_PIN, HIGH);
  }
  else {
    if (temperature < 90){
      increasingTemperature = true;
    }
    digitalWrite(RELAY_PIN, LOW);
  }
}

// convert 3 digit to a single int
int convertToInt(char hundredDigit, char tensDigit, char unitDigit){
  if (unitDigit == NULL && tensDigit == NULL){
    return hundredDigit;    
  }
  else if (unitDigit == NULL) {
    return (10*hundredDigit + tensDigit);
  }
  else{
    return (100*hundredDigit + 10*tensDigit + unitDigit);
  }
}

int convertToNumber(char digit){
  return (digit - '0');
}
