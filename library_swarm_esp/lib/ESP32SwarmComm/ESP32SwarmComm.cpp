#include "ESP32SwarmComm.h"

ESP32SwarmComm::ESP32SwarmComm(const char* ssid, const char* password, const char* mqttBroker, int mqttPort)
    : ssid(ssid), password(password), mqttBroker(mqttBroker), mqttPort(mqttPort), client(espClient) {}

void ESP32SwarmComm::setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  client.setServer(mqttBroker, mqttPort);
  client.setCallback([this](char* topic, byte* payload, unsigned int length) {
    this->callback(topic, payload, length);
  });

  while (!client.connected()) {
    if (client.connect("esp32_robot")) {
      connected = true;
    } else {
      delay(5000);
    }
  }
}

void ESP32SwarmComm::loop() {
  if (!client.connected()) {
    while (!client.connected()) {
      if (client.connect("esp32_robot")) {
        connected = true;
      } else {
        delay(5000);
      }
    }
  }
  client.loop();
}

bool ESP32SwarmComm::publish(const char* topic, const char* payload) {
  return client.publish(topic, payload);
}

bool ESP32SwarmComm::subscribe(const char* topic) {
  return client.subscribe(topic);
}

bool ESP32SwarmComm::isConnected() {
  return connected;
}

void ESP32SwarmComm::callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages here...
}
