#include <ESP32Client.h>

// Replace these values with your Wi-Fi credentials and MQTT broker details
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* mqttBroker = "your_mqtt_broker_ip";
int mqttPort = 1883;

ESP32Client client;

void messageReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  client.setupClient(ssid, password, mqttBroker, mqttPort);
  client.setMessageCallback(messageReceived);
}

void loop() {
  client.loop();
}
