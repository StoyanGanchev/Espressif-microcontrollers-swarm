#include <ESP32Broker.h>

// Replace these values with your Wi-Fi credentials and MQTT broker details
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* mqttBroker = "your_mqtt_broker_ip";
int mqttPort = 1883;

ESP32Broker broker;

void setup() {
  Serial.begin(115200);
  broker.setupBroker(ssid, password, mqttBroker, mqttPort);
}

void loop() {
  broker.loop();
}
