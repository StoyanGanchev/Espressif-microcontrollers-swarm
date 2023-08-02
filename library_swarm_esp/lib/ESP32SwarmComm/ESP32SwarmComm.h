#ifndef ESP32_SWARM_COMM_H
#define ESP32_SWARM_COMM_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

class ESP32SwarmComm {
public:
  ESP32SwarmComm(const char* ssid, const char* password, const char* mqttBroker, int mqttPort);
  void setup();
  void loop();
  bool publish(const char* topic, const char* payload);
  bool subscribe(const char* topic);
  bool isConnected();

private:
  const char* ssid;
  const char* password;
  const char* mqttBroker;
  int mqttPort;
  WiFiClient espClient;
  PubSubClient client;
  bool connected = false;
  void callback(char* topic, byte* payload, unsigned int length);
};

#endif
