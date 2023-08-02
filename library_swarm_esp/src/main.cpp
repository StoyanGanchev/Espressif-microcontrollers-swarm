#include <ESP32SwarmComm.h>

const char* wifiSSID = "YourWiFiSSID";
const char* wifiPassword = "YourWiFiPassword";
const char* mqttBroker = "YourMQTTBroker";
int mqttPort = 1883; // Default MQTT port
const char* mqttUsername = "YourMQTTUsername";
const char* mqttPassword = "YourMQTTPassword";

MyESP32Library myESP32;

void setup() {
  myESP32.setup(wifiSSID, wifiPassword, mqttBroker, mqttPort, mqttUsername, mqttPassword);
}

void loop() {
  myESP32.loop();
}
