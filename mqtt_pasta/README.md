# Control via MQTT access

## Internet and Ethernet Shield

We use an ethernet shield for internet access. The mac address is randomly attribued and the ip of the shield is given from the subnetwork for H2G2. We recommend using those parameters for further uses. If you need to add more arduino on the network, change one bit of the mac adress and 1 to the ip adress.

We recommend to scan the network before attribuing any address.

Use this command on PowerShell's windows : 

```bash
arp -a
```

## MQTT

For mqtt, we use the PubSubClient library, that can be found on the library list of arduino.

We use two topic for comunication, one for the order, and an other one for the acknowledge of the arduino.

You'll need to create an PubSubClient object

```c
PubSubClient client(server, 1883, callback, ethClient);
```

..* The server, is the brocker mqtt
..* The default port for mqtt is 1883
..* The callback function, we'll talk about it later
..* The Ethernet client object, from the shield

You'll also need to copy-paste the reconnect function, because arduino's ethernet shield is not reliable and you'll need te reconect often.

### The callback funciton

```c
void callback(char* topic, byte* payload, unsigned int length) {
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
```

We use a callback fonction to do some actions when we recieve a message. You can manipulate the topic and the data to send an acknowledge to the acknowledge topic.
