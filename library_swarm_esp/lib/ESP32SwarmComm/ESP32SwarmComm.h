#ifndef ESP32_SWARM_COMM_H
#define ESP32_SWARM_COMM_H

#include <WiFi.h>
#include <PubSubClient.h>

class MyESP32Library {
public:
  MyESP32Library();
  void setup(const char* wifiSSID, const char* wifiPassword, const char* mqttBroker, int mqttPort, const char* mqttUsername, const char* mqttPassword);
  void loop();
  void sendData(const char* topic, const char* message);
  
private:
  WiFiClient wifiClient;
  PubSubClient mqttClient;
  const char* wifiSSID;
  const char* wifiPassword;
  const char* mqttBroker;
  int mqttPort;
  const char* mqttUsername;
  const char* mqttPassword;
  unsigned long lastPublishTime;
  const unsigned long publishInterval = 5000; // 5 seconds
};
#endif
