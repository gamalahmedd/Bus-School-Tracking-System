#include "ESP01.h"


void ESP01_Init()
{
	UART1_Init();
	result = 0;
	esp_buff_len = 0;
	memset(esp_buff, 0, 100);
}

u_int8 ESP01_CheckConnection()
{	
	if(find_string(esp_buff, "OK") == 1)
	{
		result = 1;
		ESP01_ResetBuffer();
	}
	else if(find_string(esp_buff, "ERROR") == 1)
	{
		result = 0;
		ESP01_ResetBuffer();
	}
	
	return result;
}

void ESP01_ResetBuffer()
{
	memset(esp_buff, 0, esp_buff_len);
	esp_buff_len = 0;
}