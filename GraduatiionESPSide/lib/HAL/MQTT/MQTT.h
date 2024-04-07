#ifndef MQTT_H_
#define MQTT_H_
#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

void MQTT_Init(const char* mqtt_broker, const int mqtt_port);
void MQTT_connectToBroker(const char* username, const char* password);
char checkMQTTConnection();
void mqttCallback(char *topic, byte *payload, unsigned int length);
void loopMQTT();
void MQTT_Publish(const char* topic, const char* payload);
void MQTT_Subscribe(const char* topic);

#endif
