# Control via MQTT access

## Internet and Ethernet Shield

We use an ethernet shield for internet access. The mac address is randomly attribued and the ip of the shield is given from the subnetwork for H2G2. We recommend using those parameters for further uses. If you need to add more arduino on the network, change one bit of the mac adress and 1 to the ip adress.

We recommend to scan the network before attribuing any address.

Use this command on PowerShell's windows : 
```
arp -a
```

## MQTT

