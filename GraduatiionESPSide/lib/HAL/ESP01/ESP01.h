#ifndef ESP01_H_
#define ESP01_H_
#include <Arduino.h>
#include <ESP8266WiFi.h>

void ESP01_ConnectToWifi(const char* ssid, const char* password);
char ESP01_CheckConnection();

#endif