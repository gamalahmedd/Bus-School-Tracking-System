#include "../lib/MCAL/UART/UART.h"
#include "../lib/HAL/ESP01/ESP01.h"
#include "../lib/HAL/MQTT/MQTT.h"

unsigned long lastMsg = 0;
char msg[50];
char i = 0;
char flag = 0;

void setup()
{
    UART_Init();
    ESP01_ConnectToWifi("WeMO", "@mo@01014001121#");
    MQTT_Init("broker.emqx.io", 1883);
}

void loop()
{
    if(ESP01_CheckConnection() == 1)
    {
        if(!checkMQTTConnection())
        {
            Serial.println("0");
            MQTT_connectToBroker("emqx", "public");
            flag = 1;
        }
        else
        {
            if(flag == 1)
            {
                Serial.println("1");
                flag = 0;
            }
            loopMQTT();

            unsigned long now = millis();
            if(now - lastMsg > 2000)
            {
                lastMsg = now;
                while(UART_isAvailable())
                {
                    msg[i] = UART_Receive();
                    i++;
                }
                i = 0;
                MQTT_Publish("emqx/esp8266", msg);
            }
        }
    }
    else
    {
        Serial.println("0");
        ESP01_ConnectToWifi("WeMO", "@mo@01014001121#");
        flag = 1;
    }
}