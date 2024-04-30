#include "MQTT.h"

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

void MQTT_Init(const char* mqtt_broker, const int mqtt_port)
{
    mqtt_client.setServer(mqtt_broker, mqtt_port);
    mqtt_client.setCallback(mqttCallback);
}

void MQTT_connectToBroker(const char* username, const char* password)
{
    while (!mqtt_client.connected()) 
    {
        Serial.println("Connecting to broker...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (mqtt_client.connect(clientId.c_str(), username, password))
        {
            Serial.println("Connected to Broker");
            MQTT_Publish("emqx/esp8266", "Controller Connected");
        } 
        else
        {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
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

void mqttCallback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message received on topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
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