   
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

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(172, 17, 4, 44);
// broker.hivemq.com 18.184.104.180
IPAddress server(18, 184, 104, 180);

const char* inTopic = "ecam/pastaBot/cookTime/";
const char* outTopic = "ecam/pastaBot/response/";

int tim;
bool cook = false;
// Callback function header
void callback(char* topic, byte* payload, unsigned int length);

EthernetClient ethClient;
PubSubClient client(server, 1883, callback, ethClient);

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


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("arduinoClient")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(outTopic,"hello world");
      // ... and resubscribe
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup()
{
  Serial.begin(57600);
  Ethernet.begin(mac, ip);
  if (client.connect("arduinoClient")) {
    Serial.println("connected at the first try");
    client.subscribe(inTopic);
  }
}



void loop()
{
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if (cook == true){
     Serial.println(tim);
  }
}
