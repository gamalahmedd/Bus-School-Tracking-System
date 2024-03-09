#include "ESP01.h"
#include <avr/interrupt.h>

void ESP01_Init()
{
	//Configurations
	GIE_Enable();
	DIO_ConfigChannel(DIO_ChannelD0, OUTPUT);
	UART1_Init();
	
	//Setup
	data_ready = 0;
	data_len = 0;
	memset(rx_buff, 0, 500);
	
	//Reset Wifi
	UART1_TransmitString("Resetting Wifi");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("Please Wait...");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	ESP01_Reset_Wifi();
	while(ESP01_ResponseSuccess() != Ready)
	{
		ESP01_Reset_Wifi();
	}
	_delay_ms(100);
	
	//Send AT
	UART1_TransmitString("Sending AT");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("Please Wait...");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("AT");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	while(ESP01_ResponseSuccess() != OK)
	{
		UART1_TransmitString("AT");
		UART1_Transmit(CR);
		UART1_Transmit(LF);
	}
	_delay_ms(100);
	
	//Set working mode to station mode and AP
	UART1_TransmitString("Setting Mode");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("Please Wait...");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("AT+CWMODE=3");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	while (ESP01_ResponseSuccess() != OK)
	{
		UART1_TransmitString("AT+CWMODE=3");
		UART1_Transmit(CR);
		UART1_Transmit(LF);
	}
	_delay_ms(1000);
	
	//Enable Single Connection
	UART1_TransmitString("Setting Connection");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("Please Wait...");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("AT+CIPMUX=0");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	while (ESP01_ResponseSuccess() != OK)
	{
		UART1_TransmitString("AT+CIPMUX=0");
		UART1_Transmit(CR);
		UART1_Transmit(LF);
	}
	_delay_ms(1000);
}

void ESP01_Connect_Wifi(u_int8 SSID[], u_int8 Password[])
{
	while(1)
	{
		u_int8 flag;
		UART1_TransmitString("Connecting to Wifi...");
		UART1_Transmit(CR);
		UART1_Transmit(LF);
		UART1_TransmitString("AT+CWJAP=");
		UART1_TransmitString(SSID);
		UART1_Transmit(',');
		UART1_TransmitString(Password);
		UART1_Transmit(CR);
		UART1_Transmit(LF);
		_delay_ms(10000);
		flag = ESP01_Check_Wifi_Connection(SSID);
		if(flag == NO_AP)
		{
			UART1_TransmitString("Try Again!");
			UART1_Transmit(CR);
			UART1_Transmit(LF);
		}
		else if(flag == Connected)
		{
			UART1_TransmitString("Connected Successfully");
			UART1_Transmit(CR);
			UART1_Transmit(LF);
			break;
		}
	}
	_delay_ms(1000);
}

u_int8 ESP01_Check_Wifi_Connection(u_int8 SSID[])
{
	//Check if wifi connected to an access point
	ESP01_Reset_Buffer();
	u_int8 result = 0;
	UART1_TransmitString("Check Connection to AP");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("Please Wait...");
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	while(result != Connected && result != NO_AP)
	{
		UART1_TransmitString("AT+CWJAP?");
		UART1_Transmit(CR);
		UART1_Transmit(LF);
		while(!data_ready);
		if(find_string(rx_buff, "No AP") == 1) {result = NO_AP;}
		else if(find_string(rx_buff, SSID) == 1) {result = Connected;}
		else result = 0;
	}
	ESP01_Reset_Buffer();
	return result;
}

u_int8 ESP01_ResponseSuccess()
{
	u_int8 result;
	
	while(!data_ready);
	
	if(find_string(rx_buff, "OK") == 1) {result = OK;}
	else if(find_string(rx_buff, "no change") == 1) {result = no_change;}
	else if(find_string(rx_buff, "ready") == 1) {result = Ready;}
	else if(find_string(rx_buff, ">") == 1) {result = send_ready;}
	else result = 0;
	
	ESP01_Reset_Buffer();
	return result;
}

void ESP01_Reset_Buffer()
{
	memset(rx_buff, 0, data_len);
	
	//reset variables used with buffer
	data_len = 0;
	data_ready = 0;
}

void ESP01_Reset_Wifi()
{
	DIO_WriteChannel(DIO_ChannelD0, STD_HIGH);
	_delay_ms(500);
	DIO_WriteChannel(DIO_ChannelD0, STD_LOW);
}


ISR(USART1_RX_vect)
{
	temp = UDR1_Register;
	switch(temp)
	{
		case LF:
			if(data_len > 1)
			{
				data_ready = 1;
			}
			break;
		case CR:
			rx_buff[data_len] = 0;
			break;
		default:
			rx_buff[data_len] = temp;
			data_len++;
			break;
	}
}