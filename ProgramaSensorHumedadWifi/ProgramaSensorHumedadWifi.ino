#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include "UbidotsMicroESP8266.h"
#define TOKEN  "BBFF-xiRMq3c9tX99rsp8ClKIGvuaAeRzc8"  // Put here your Ubidots TOKEN
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
String inString = "";    // string to hold input
Ubidots client(TOKEN);
#define LED 16

void setup() {
    // put your setup code here, to run once:
    pinMode(LED,OUTPUT);
    digitalWrite(LED,LOW);
    Serial.begin(115200);

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("Sensor_Humedad");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    
    //if you get here you have connected to the WiFi
    Serial.println("Conectado!");
     digitalWrite(LED,HIGH);
     delay(100);
     digitalWrite(LED,LOW);
     delay(100);
     digitalWrite(LED,HIGH);
     delay(100);
     digitalWrite(LED,LOW);
     delay(100);
     

}

void loop() {
  digitalWrite(LED,HIGH);
     while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
        if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      //client.add(ID_1,inString.toInt());
      client.add("humedad",inString.toInt());
      client.sendAll(true);
      // clear the string for new input:
      inString = "";
      delay(500);
    }
  }
    // put your main code here, to run repeatedly:
    
}
