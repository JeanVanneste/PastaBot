unsigned long time;
bool increasingTemperature = true;

void setup() {
  Serial.begin(9600);
  Serial.print("Hello world!\n");

  pinMode(7, OUTPUT);
  time = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  int temperature = 0;
  
  temperature = getTemperature(time);
  //Serial.print(temperature);
  //Serial.print(" ");
  //Serial.print( increasingTemperature ? "increase\n": "decrease\n");
  changeRelayState(temperature, increasingTemperature);
}


int getTemperature(unsigned long time){
    if (millis() - time > 6000)
      return 98;
    else if (millis() - time > 5000)
      return 97;
    else if (millis() - time > 4000)
      return 85;
    else if (millis() - time > 3000)     
      return 95;
    else if (millis() - time > 2000)
      return 105;
    else
      return 80;
}

void changeRelayState(int temperature, bool increasingTemperature){
  if (increasingTemperature) {
    if (temperature > 100){
      increasingTemperature = false;
    }
    digitalWrite(7, LOW);
  }
  else {
    if (temperature < 90){
      increasingTemperature = true;
    }
    digitalWrite(7, HIGH);
  }
}
