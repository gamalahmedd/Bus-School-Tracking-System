#include "ESP01.h"

void ESP01_ConnectToWifi(const char* ssid, const char* password)
{
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("Connected Successfully!");
}

char ESP01_CheckConnection()
{
    char result;

    if(WiFi.status() == WL_CONNECTED)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;
}