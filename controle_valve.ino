void FillWater(){
  digitalWrite(solenoidPin, HIGH);
  delay(HalfFillingTime);
  //delay(HalfFillingTime);
  //delay(HalfFillingTime);
  //delay(HalfFillingTime);

  digitalWrite(solenoidPin, LOW);
  delay(5000);
}

void EmptyWater(){
  digitalWrite(solenoidEmptyWater, HIGH);
  delay(HalfEmptyingTime);
  //delay(HalfEmptyingTime);
  //delay(HalfEmptyingTime);
  //delay(HalfEmptyingTime);
  digitalWrite(solenoidEmptyWater, LOW);
  delay(5000);
}
