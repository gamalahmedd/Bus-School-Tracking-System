#include "ESP01.h"
#include <avr/interrupt.h>


void ESP01_Init()
{
	GIE_Enable();
	UART1_Init();
	result = 0;
	data_len = 0;
	memset(rx_buff, 0, 500);
}

u_int8 ESP01_CheckConnection()
{	
	if(find_string(rx_buff, "OK") == 1)
	{
		result = 1;
		ESP01_ResetBuffer();
	}
	else if(find_string(rx_buff, "ERROR" == 1))
	{
		result = 0;
		ESP01_ResetBuffer();
	}
	
	return result;
}

void ESP01_ResetBuffer()
{
	memset(rx_buff, 0, data_len);
	data_len = 0;
}

ISR(USART1_RX_vect)
{
	temp = UDR1_Register;
	rx_buff[data_len] = temp;
	data_len++;
	if(data_len == 500)
		ESP01_ResetBuffer();
}