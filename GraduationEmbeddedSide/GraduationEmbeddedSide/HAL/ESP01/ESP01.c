#include "ESP01.h"
#include <avr/interrupt.h>

u_int8 webpage_request1[] =
"<meta http-equiv=\"refresh\" content=\"10\">\
<html>\
<body>\
<h1>Counter Value = ";
u_int8 webpage_request2[] = "</h1></body></html>";

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
	UART1_sendATCommand("Resetting Wifi");
	UART1_sendATCommand("Please Wait...");
	ESP01_Reset_Wifi();
	while(ESP01_ResponseSuccess() != Ready)
	{
		ESP01_Reset_Wifi();
	}
	_delay_ms(100);
	
	//Send AT
	UART1_sendATCommand("Sending AT");
	UART1_sendATCommand("Please Wait...");
	UART1_sendATCommand("AT");
	while(ESP01_ResponseSuccess() != OK)
	{
		UART1_sendATCommand("AT");
	}
	_delay_ms(100);
	
	//Set working mode to station mode and AP
	UART1_sendATCommand("Setting Mode");
	UART1_sendATCommand("Please Wait...");
	UART1_sendATCommand("AT+CWMODE=3");
	while (ESP01_ResponseSuccess() != OK)
	{
		UART1_sendATCommand("AT+CWMODE=3");
	}
	_delay_ms(1000);
	
	//Enable Single Connection
	UART1_sendATCommand("Setting Connection");
	UART1_sendATCommand("Please Wait...");
	UART1_sendATCommand("AT+CIPMUX=1");
	while (ESP01_ResponseSuccess() != OK)
	{
		UART1_sendATCommand("AT+CIPMUX=1");
	}
	_delay_ms(1000);
}

void ESP01_Connect_Wifi(u_int8 SSID[], u_int8 Password[])
{
	while(1)
	{
		u_int8 flag;
		UART1_sendATCommand("Connecting to Wifi...");
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
			UART1_sendATCommand("Try Again!");
		}
		else if(flag == Connected)
		{
			UART1_sendATCommand("Connected Successfully");
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
	UART1_sendATCommand("Check Connection to AP");
	UART1_sendATCommand("Please Wait...");
	while(result != Connected && result != NO_AP)
	{
		UART1_sendATCommand("AT+CWJAP?");
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

void ESP01_GetIP_MAC_Addresses()
{
	u_int8 flag;
	UART1_sendATCommand("Getting IP & MAC Addresses...");
	while(flag != OK)
	{
		UART1_sendATCommand("AT+CIFSR");
		while(!data_ready);
		if(find_string(rx_buff, "OK") == 1)
		{
			flag = OK;
		}	
		else
		{
			flag = 0;
		}
	}
	
	UART1_TransmitString("APIP=");
	find_get_string(rx_buff, "APIP,\"", 6, "\"", 0, APIP);
	UART1_TransmitString(APIP);
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("APMAC=");
	find_get_string(rx_buff, "APMAC,\"", 7, "\"", 0, APMAC);
	UART1_TransmitString(APMAC);
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("STAIP=");
	find_get_string(rx_buff, "STAIP,\"", 7, "\"", 0, STAIP);
	UART1_TransmitString(STAIP);
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	UART1_TransmitString("STAMAC=");
	find_get_string(rx_buff, "STAMAC,\"", 8, "\"", 0, STAMAC);
	UART1_TransmitString(STAMAC);
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	ESP01_Reset_Buffer();
}

void ESP01_Create_TCPServer(u_int8* portNumber)
{
	UART1_sendATCommand("Create TCP Server...");
	UART1_TransmitString("AT+CIPSERVER=1,");
	UART1_TransmitString(portNumber);
	UART1_Transmit(CR);
	UART1_Transmit(LF);
	while(ESP01_ResponseSuccess() != OK)
	{
		UART1_TransmitString("AT+CIPSERVER=1,");
		UART1_TransmitString(portNumber);
		UART1_Transmit(CR);
		UART1_Transmit(LF);
	}
	_delay_ms(1000);
	ESP01_Reset_Buffer();
}

void ESP01_Check_Request()
{
	if(data_ready)
	{
		if(find_string(rx_buff, "+IPD") == 1)
		{
			_delay_ms(500); //waiting before getting connection id
			
			//get connection id
			memset(connection_id, 0, 5);
			find_get_string(rx_buff, "+IPD,", 5, ",", 0, connection_id);
			
			size_data = get_size_Data();
			memset(size_data_text, 0, 10);
			itoa(size_data, size_data_text, 10);
			
			ESP01_Reset_Buffer();
			UART1_TransmitString("AT+CIPSEND=");
			UART1_TransmitString(connection_id);
			UART1_Transmit(',');
			UART1_sendATCommand(size_data_text);
			ESP01_Reset_Buffer();
			
			UART1_TransmitString(webpage_request1);
			UART1_TransmitString(counter_text);
			UART1_TransmitString(webpage_request2);
			
			ESP01_Reset_Buffer();
			UART1_TransmitString("AT+CIPCLOSE=");
			UART1_sendATCommand(connection_id);
			_delay_ms(1000);
			while(ESP01_ResponseSuccess() != OK)
			{
				UART1_TransmitString("AT+CIPCLOSE=");
				UART1_sendATCommand(connection_id);
				_delay_ms(1000);
			}
			ESP01_Reset_Buffer();
		}
	}
}

u_int16 get_size_Data()
{
	u_int16 size = 0;
	
	//get size of DATA to be sent
	size = strlen(webpage_request1);
	size += strlen(counter_text);
	size += strlen(webpage_request2);
	
	return size;
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