#include "UART.h"

void UART_Init()
{
    Serial.begin(9600);
}

void UART_Transmit(char* data)
{
    Serial.println(data);
}


char UART_Receive()
{
    char data_receive;
    data_receive = Serial.read();
    return data_receive;
}

char UART_isAvailable()
{
    if(Serial.available())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}