#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "Secret_config.h"

String inString = "";    // string to hold input
#define LED 16

//MQTT 
const char* mqttServer = MQTT_SERVER ;
const int mqttPort = MQTT_PORT;
const char* mqttUser = MQTT_USER;
const char* mqttPassword =MQTT_PASSWORD;
const char* topico =TOPICO;
// Cliente ESP en el Broker mqtt

WiFiClient espClient;
PubSubClient client(espClient);

int mqttCon=0;
int trys=0;
void callback(char* topic, byte* payload, unsigned int length) {
 
  for (int i = 0; i< length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println(" ");

}
// Reconexión al Broker MQTT



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID

    // Attempt to connect
    if (client.connect("TDTSENSOR", mqttUser, mqttPassword)) {
      Serial.println("connected");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
    pinMode(LED,OUTPUT);
    digitalWrite(LED,LOW);
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP

    // put your setup code here, to run once:
    Serial.begin(115200);
    
    // WiFi.mode(WiFi_STA); // it is a good practice to make sure your code sets wifi mode how you want it.

    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wm;

 


    bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    res = wm.autoConnect("TDT_Sensor","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        // ESP.restart();
    } 
    else {
        //if you get here you have connected to the WiFi    
        Serial.println("connected...yeey :)");
          client.setServer(mqttServer, 1883);
        client.setCallback(callback);
         client.publish(topico,"alive");
    }



}

void loop() {


  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  
    while (Serial.available() > 0) 
    {int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        inString += (char)inChar;
      }
        if (inChar == '\n') {
        Serial.print("Value:");
        Serial.println(inString.toInt());

        int str_len = inString.length() + 1; 
        char char_array[str_len];
        inString.toCharArray(char_array, str_len);
        client.publish(topico,char_array);
        inString = "";
        delay(500);
      
    }
  }
    
}
