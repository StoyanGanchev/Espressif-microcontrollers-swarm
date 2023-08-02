#include "connection_and_communication.h"

MQTTConnection::MQTTConnection(const char* ssid, const char* password, const char* mqttBroker, int mqttPort,
                               const char* mqttUsername, const char* mqttPassword)
  : ssid(ssid), password(password), mqttBroker(mqttBroker), mqttPort(mqttPort),
    mqttUsername(mqttUsername), mqttPassword(mqttPassword), client(espClient) {}

void MQTTConnection::setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  client.setServer(mqttBroker, mqttPort);
  client.setCallback(mqttCallback);

  while (!client.connected()) {
    if (client.connect("ESP32Client", mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT Broker");
    } else {
      Serial.print("MQTT connection failed, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void MQTTConnection::loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void MQTTConnection::reconnect() {
  while (!client.connected()) {
    Serial.println("Reconnecting to MQTT Broker...");
    if (client.connect("ESP32Client", mqttUsername, mqttPassword)) {
      Serial.println("Connected to MQTT Broker");
    } else {
      Serial.print("MQTT connection failed, retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void MQTTConnection::setCallback(void (*callback)(char*, byte*, unsigned int)) {
  client.setCallback(callback);
}

void MQTTConnection::publishMessage(const char* topic, const char* payload) {
  client.publish(topic, payload);
}

bool MQTTConnection::isConnected() {
  return client.connected();
}

bool MQTTConnection::subscribe(const char* topic) {
  return client.subscribe(topic);
}

// Define the callback function (must be static)
void MQTTConnection::mqttCallback(char* topic, byte* payload, unsigned int length) {
  // Your callback implementation here
  // Note: As this function is static, you can only access static member variables
  //       if needed, you may need to use other mechanisms to communicate with the instance of the class.
}
