#ifndef ESP32Client_h
#define ESP32Client_h

#include <WiFi.h>
#include <PubSubClient.h>

class ESP32Client {
public:
  ESP32Client();
  void setupClient(const char* ssid, const char* password, const char* mqttBroker, int mqttPort);
  void loop();
  void setMessageCallback(void (*callback)(char*, byte*, unsigned int));
  
private:
  WiFiClient wifiClient;
  PubSubClient mqttClient;
  const char* ssid;
  const char* password;
  const char* mqttBroker;
  int mqttPort;
};

#endif
