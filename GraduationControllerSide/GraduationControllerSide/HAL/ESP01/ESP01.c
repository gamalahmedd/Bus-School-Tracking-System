#include "ESP01.h"


void ESP01_Init()
{
	UART1_Init();
	result = 0;
	esp_buff_len = 0;
	memset(esp_buff, 0, 1000);
}

u_int8 ESP01_CheckConnection()
{	
	if(find_string(esp_buff, "ESP CONNECTED") == 1)
	{
		result = 3;
		ESP01_ResetBuffer();
	}
	else if(find_string(esp_buff, "ESP NOT CONNECTED") == 1)
	{
		result = 2;
		ESP01_ResetBuffer();
	}
	
	return result;
}

void ESP01_ResetBuffer()
{
	memset(esp_buff, 0, esp_buff_len);
	esp_buff_len = 0;
}