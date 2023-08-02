#ifndef CONNECTION_AND_COMMUNICATION_H
#define CONNECTION_AND_COMMUNICATION_H

#include <WiFi.h>
#include <PubSubClient.h>

class MQTTConnection {
public:
  MQTTConnection(const char* ssid, const char* password, const char* mqttBroker, int mqttPort,
                 const char* mqttUsername = nullptr, const char* mqttPassword = nullptr);
  void setup();
  void loop();
  void reconnect();
  void setCallback(void (*callback)(char*, byte*, unsigned int));
  void publishMessage(const char* topic, const char* payload);
  bool isConnected();
  bool subscribe(const char* topic); // New function for subscribing to a topic

private:
  const char* ssid;
  const char* password;
  const char* mqttBroker;
  int mqttPort;
  const char* mqttUsername;
  const char* mqttPassword;
  WiFiClient espClient;
  PubSubClient client;

  // Declare callback function as a static member function
  static void mqttCallback(char* topic, byte* payload, unsigned int length);
};

#endif
