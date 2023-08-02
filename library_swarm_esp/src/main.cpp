#include <ESP32SwarmComm.h>

// Replace with your Wi-Fi network credentials and MQTT broker information
const char* ssid = "your_wifi_ssid";
const char* password = "your_wifi_password";
const char* mqttBroker = "your_mqtt_broker_address";
const int mqttPort = 1883; // Default MQTT port

ESP32SwarmComm swarmComm(ssid, password, mqttBroker, mqttPort);

void setup() {
  Serial.begin(115200);
  delay(2000);
  swarmComm.setup();
}

void loop() {
  swarmComm.loop();
  // Your main swarm behavior code goes here...
}
