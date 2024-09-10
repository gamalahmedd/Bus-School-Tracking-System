#include "MQTT.h"

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void MQTT_Init(const char* mqtt_broker, const int mqtt_port)
{
    mqtt_client.setServer(mqtt_broker, mqtt_port);
}

void MQTT_connectToBroker(const char* username, const char* password)
{
    Serial.println("Attempting MQTT connection...");
    if (!mqtt_client.connected()) 
    {
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (mqtt_client.connect(clientId.c_str(), username, password))
        {
            MQTT_Publish("bus/welcome", "Controller Connected");
            Serial.println("MQTT Connected");
        } 
        else
        {
            delay(5000);
        }
    }
}

char checkMQTTConnection()
{
    char result;
    if(mqtt_client.connected())
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;
}

void loopMQTT()
{
    mqtt_client.loop();
}

void MQTT_Publish(const char* topic, const char* payload)
{
    mqtt_client.publish(topic, payload, true);
}

void MQTT_Subscribe(const char* topic)
{
    mqtt_client.subscribe(topic);
}