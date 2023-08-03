#include "ESP8266Client.h"

ESP8266Client::ESP8266Client() : mqttClient(wifiClient) {
  // Initialize variables
}

void ESP8266Client::setupClient(const char* ssid, const char* password, const char* mqttBroker, int mqttPort) {
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

void ESP8266Client::loop() {
  if (!mqttClient.connected()) {
    if (mqttClient.connect("ESP8266Client")) {
      Serial.println("Connected to MQTT broker");
      mqttClient.subscribe("topic/test"); // Subscribe to the topic from the broker
    }
  }

  mqttClient.loop();
}

void ESP8266Client::setMessageCallback(void (*callback)(char*, byte*, unsigned int)) {
  mqttClient.setCallback(callback);
}
