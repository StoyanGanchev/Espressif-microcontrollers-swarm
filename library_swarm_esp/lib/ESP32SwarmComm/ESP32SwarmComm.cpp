#include "ESP32SwarmComm.h"

MyESP32Library::MyESP32Library() {
  lastPublishTime = 0;
}

void MyESP32Library::setup(const char* wifiSSID, const char* wifiPassword, const char* mqttBroker, int mqttPort, const char* mqttUsername, const char* mqttPassword) {
  this->wifiSSID = wifiSSID;
  this->wifiPassword = wifiPassword;
  this->mqttBroker = mqttBroker;
  this->mqttPort = mqttPort;
  this->mqttUsername = mqttUsername;
  this->mqttPassword = mqttPassword;
  
  Serial.begin(115200);
  WiFi.begin(wifiSSID, wifiPassword);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi.");
  mqttClient.setServer(mqttBroker, mqttPort);
}

void MyESP32Library::loop() {
  if (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    
    if (mqttClient.connect("ESP32Client", mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT broker.");
    } else {
      Serial.print("MQTT connection failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(". Retrying in 5 seconds...");
      delay(5000);
      return;
    }
  }

  mqttClient.loop();

  unsigned long currentMillis = millis();
  if (currentMillis - lastPublishTime >= publishInterval) {
    sendData("topic/1", "Hello from ESP32!");
    lastPublishTime = currentMillis;
  }
}

void MyESP32Library::sendData(const char* topic, const char* message) {
  mqttClient.publish(topic, message);
}
