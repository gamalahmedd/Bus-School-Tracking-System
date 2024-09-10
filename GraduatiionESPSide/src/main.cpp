#include "../lib/MCAL/UART/UART.h"
#include "../lib/HAL/ESP01/ESP01.h"
#include "../lib/HAL/MQTT/MQTT.h"
#include "../lib/LIB/String_Find.h"

unsigned long lastMsg = 0;
char msg_len;
char flag = 0;
char msg[50];
char msg_send[50];

void setup()
{
    UART_Init();
    ESP01_ConnectToWifi("Jimmy", "11223344");
    MQTT_Init("broker.emqx.io", 1883);
    memset(msg, 0, 50);
    msg_len = 0;
    memset(msg_send, 0, 50);
}

void loop()
{
    if(ESP01_CheckConnection() == 1)
    {
        if(!checkMQTTConnection())
        {
            Serial.println("ESP NOT CONNECTED");
            MQTT_connectToBroker("emqx", "public");
            flag = 1;
        }
        else
        {
            if(flag == 1)
            {
                Serial.println("ESP CONNECTED");
                flag = 0;
            }
            loopMQTT();

            unsigned long now = millis();
            if(now - lastMsg > 2000)
            {
                lastMsg = now;
                while(UART_isAvailable())
                {
                    msg[msg_len] = UART_Receive();
                    msg_len++;
                } 
                if(find_string(msg, "RFID-") == 1)
                {
                    find_get_string(msg, "RFID-", 5, "RFID", 0, msg_send);
                    MQTT_Publish("bus/attendance", msg_send);
                    memset(msg, 0, msg_len);
                    memset(msg_send, 0, 50);
                    msg_len = 0;
                } 
                else if(find_string(msg, "GPS-") == 1)
                {
                    find_get_string(msg, "GPS-", 4, "GPS", 0, msg_send);
                    MQTT_Publish("bus/location", msg_send);
                    memset(msg, 0, msg_len);
                    memset(msg_send, 0, 50);
                    msg_len = 0;
                }
                else if(find_string(msg, "ADXL-Acceleration") == 1)
                {
                    MQTT_Publish("bus/alert", "Acceleration");
                    memset(msg, 0, msg_len);
                    memset(msg_send, 0, 50);
                    msg_len = 0;
                }
                else if(find_string(msg, "ADXL-Accident") == 1)
                {
                    MQTT_Publish("bus/alert", "Accident");
                    memset(msg, 0, msg_len);
                    memset(msg_send, 0, 50);
                    msg_len = 0;
                }
            }
        }
    }
    else
    {
        Serial.println("ESP NOT CONNECTED");
        ESP01_ConnectToWifi("Jimmy", "11223344");
        flag = 1;
    }
}