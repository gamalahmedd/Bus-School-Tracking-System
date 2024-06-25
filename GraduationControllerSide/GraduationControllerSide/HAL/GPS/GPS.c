#include "GPS.h"

void GPS_Init()
{
	UART0_Init();
	gps_buff_len = 0;
	memset(gps_buff, 0, 500);
}

void getGPSLocation()
{
	gps_buff[gps_buff_len] = UART0_Receive();
	gps_buff_len++;
}

void GPS_Buffer_Reset()
{
	memset(gps_buff, 0, gps_buff_len);
	gps_buff_len = 0;
}