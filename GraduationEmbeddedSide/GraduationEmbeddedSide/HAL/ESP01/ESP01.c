#include "ESP01.h"
#include <avr/interrupt.h>


void ESP01_Init()
{
	GIE_Enable();
	UART1_Init();
	result = 0;
	data_ready = 0;
	data_len = 0;
	memset(rx_buff, 0, 50);
}

u_int8 ESP01_CheckConnection()
{	
	if(find_string(rx_buff, "1") == 1) {result = 1;}
	else if(find_string(rx_buff, "0" == 1)){result = 0;}
		
	ESP01_ResetBuffer();
}

void ESP01_ResetBuffer()
{
	memset(rx_buff, 0, data_len);
	data_len = 0;
	data_ready = 0;
}

ISR(USART1_RX_vect)
{
	temp = UDR1_Register;
	rx_buff[data_len] = temp;
	data_len++;
}