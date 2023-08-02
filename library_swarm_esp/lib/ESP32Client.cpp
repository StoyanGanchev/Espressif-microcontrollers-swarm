#include "ESP32Client.h"

ESP32Client::ESP32Client() : mqttClient(wifiClient) {
  // Initialize variables
}

void ESP32Client::setupClient(const char* ssid, const char* password, const char* mqttBroker, int mqttPort) {
  this->ssid = ssid;
  this->password = password;
  this->mqttBroker = mqttBroker;
  this->mqttPort = mqttPort;

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnected to Wi-Fi");
  
  mqttClient.setServer(mqttBroker, mqttPort);
}

void ESP32Client::loop() {
  if (!mqttClient.connected()) {
    if (mqttClient.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe("topic/test"); // Subscribe to the topic from the broker
    }
  }

  mqttClient.loop();
}

void ESP32Client::setMessageCallback(void (*callback)(char*, byte*, unsigned int)) {
  mqttClient.setCallback(callback);
}
