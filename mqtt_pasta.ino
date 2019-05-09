   
/*
 Publishing in the callback
  - connects to an MQTT server
  - subscribes to the topic "inTopic"
  - when a message is received, republishes it to "outTopic"
  This example shows how to publish messages within the
  callback function. The callback function header needs to
  be declared before the PubSubClient constructor and the
  actual callback defined afterwards.
  This ensures the client reference in the callback function
  is valid.
*/



// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // In order to republish this payload, a copy must be made
  // as the orignal payload buffer will be overwritten whilst
  // constructing the PUBLISH packet.

  // Allocate the correct amount of memory for the payload copy

  Serial.print("Time arrived [");
  int recieved = String(String((char*)payload).charAt(0)).toInt();
  if (recieved != 0){
    tim = recieved;
    cook = true;
    Serial.print(tim);
    Serial.println("] ");
    byte* p = (byte*) "ok";
    Serial.println((char*)p);
    // Copy the payload to the new buffer
    client.publish(outTopic, p, length);
  }
  else {
    cook = false;
  }

}
