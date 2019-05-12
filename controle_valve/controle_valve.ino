const int FillingTime = 1000*10;
const int EmptyingTime = 1000*3;
int solenoidPin = 4;    // pin for solenoid filling
int solenoidEmptyWater = 6; // pin for solenoid emptying
int Fill = 7; //pin for activate filling
int Empty = 8; //pin for activate emptying

void setup() {
  // put your setup code here, to run once:
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
  pinMode(solenoidFillWater, OUTPUT);
  pinMode(solenoidEmptyWater, OUTPUT);
  pinMode(Fill, INPUT);
  pinMode(Empty, INPUT);
  digitalWrite(solenoidPin, LOW);
  digitalWrite(solenoidFillWater, LOW);
  digitalWrite(solenoidEmptyWater, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*while(digitalRead(Fill) == LOW && digitalRead(Empty) == LOW)
  ;*/
  /*digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
  delay(1000);                      //Wait 1 Second
  digitalWrite(solenoidPin, LOW);     //Switch Solenoid OFF
  delay(1000);                      //Wait 1 Second*/
  while((digitalRead(Fill) ==LOW)&&(digitalRead(Empty)== LOW)) {
    
  }
  ;
  if(digitalRead(Empty) == HIGH){
    EmptyWater();
  }
  else if(digitalRead(Fill)==HIGH){
    FillWater();
  }
   
}

void FillWater(){
  digitalWrite(solenoidPin, HIGH);
  delay(FillingTime);
  digitalWrite(solenoidPin, LOW);
  delay(5000);
}

void EmptyWater(){
  digitalWrite(solenoidEmptyWater, HIGH);
  delay(EmptyingTime);
  digitalWrite(solenoidEmptyWater, LOW);
  delay(5000);
}
