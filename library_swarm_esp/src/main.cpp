#include <Arduino.h>
#include "connection_and_communication.h"

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqttBroker = "MQTT_BROKER_IP";
const int mqttPort = 1883;
const char* mqttUsername = "MQTT_USERNAME"; // Optional, if your broker requires authentication
const char* mqttPassword = "MQTT_PASSWORD"; // Optional, if your broker requires authentication

MQTTConnection mqttConnection(ssid, password, mqttBroker, mqttPort, mqttUsername, mqttPassword);

// Callback function to be executed when an MQTT message is received
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message [");
  Serial.print(topic);
  Serial.print("]: ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Add your custom logic based on the received MQTT message here
}

void setup() {
  Serial.begin(115200);

  mqttConnection.setup();

  // Set the callback function to be executed when an MQTT message is received
  mqttConnection.setCallback(mqttCallback);

  // Subscribe to the desired MQTT topic
  mqttConnection.subscribe("esp32/command");
}

void loop() {
  if (!mqttConnection.isConnected()) {
    mqttConnection.reconnect();
  }
  mqttConnection.loop();

  // Your main application code here
}
