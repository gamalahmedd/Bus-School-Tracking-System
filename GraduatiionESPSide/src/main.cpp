#include "../lib/MCAL/UART/UART.h"
#include "../lib/HAL/ESP01/ESP01.h"
#include "../lib/HAL/MQTT/MQTT.h"
#include "../lib/LIB/String_Find.h"

unsigned long lastMsg = 0;
unsigned char msg[100];
unsigned char msg_len;
unsigned char flag = 0;

void setup()
{
    UART_Init();
    ESP01_ConnectToWifi("WeMO", "@mo@01014001121#");
    MQTT_Init("broker.emqx.io", 1883);
    memset(msg, 0, 100);
    msg_len = 0;
}

void loop()
{
    if(ESP01_CheckConnection() == 1)
    {
        if(!checkMQTTConnection())
        {
            Serial.println("ERROR");
            MQTT_connectToBroker("emqx", "public");
            flag = 1;
        }
        else
        {
            if(flag == 1)
            {
                Serial.println("OK");
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
                    msg_len++;
                }
                if(find_string(msg, "RFID") == 1)
                {

                }
                else if(find_string(msg, "GPS") == 1)
                {

                }
                else if(find_string(msg, "ADXL") == 1)
                {
                    
                }
            }
        }
    }
    else
    {
        Serial.println("ERROR");
        ESP01_ConnectToWifi("WeMO", "@mo@01014001121#");
        flag = 1;
    }
}