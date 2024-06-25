#include "service.h"
#define ESP_PRIORITY 9
#define GPS_PRIORITY 8

QueueHandle_t CHECK_CONNECTION;

portSHORT startScheduler()
{
	System_Init();
	
	ESP_SEM = xSemaphoreCreateCounting(1, 0);
	xTaskCreate(ESP01_CheckConnectionTask, "CheckConnection", configMINIMAL_STACK_SIZE, NULL, ESP_PRIORITY, NULL);
	xTaskCreate(GPS_GetLocationTask, "GPSLocation", 200, NULL, GPS_PRIORITY, NULL);
	xTaskCreate(RFID_TakeAttendance, "RFIDAttendance", 200, NULL, RFID_PRIORITY, NULL);
	
	vTaskStartScheduler();
}

void System_Init()
{
	GIE_Enable();
	ESP01_Init();
	DIO_ConfigChannel(DIO_ChannelG0, OUTPUT);
	DIO_ConfigPullUp(DIO_ChannelG0, DISABLE);
	GPS_Init();
	LCD_Init();
	mfrc522_init();
}

/*-------------------------------------------------------ESP Task--------------------------------------------*/

void ESP01_CheckConnectionTask(void *pvParam)
{
	u_int8 ret = 0;
	while(1)
	{
		ret = xSemaphoreTake(ESP_SEM, 100);
		if(ret == 1)
		{
			if(ESP01_CheckConnection() == 1)
			{
				
			}
			else
			{
				
			}
		}
		else
		{
			
		}
	}
	
}


/*--------------------------------------------------------GPS Task-----------------------------------------------*/

void GPS_GetLocationTask(void *pvParam)
{
	char longitude[15];
	char latitude[15];
	while(1)
	{
		getGPSLocation();
		if(find_string(gps_buff, "$GPRMC") == 1)
		{
			memset(longitude, 0, 15);
			memset(latitude, 0, 15);
			find_get_string(gps_buff, "$GPGLL,", 7, ",", 0, latitude);
			find_get_string(gps_buff, latitude, 14, ",", 0, longitude);
			GPS_Buffer_Reset();
		}
		else
		{
			
		}
		vTaskDelay(100);
	}
}

/*--------------------------------------------------------RFID Task-------------------------------------------------------*/

void RFID_TakeAttendance(void *pvParam)
{
	u_int8 byte;
	u_int8 str[MAX_LEN];

	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);
	
	while(1)
	{
		byte = mfrc522_request(PICC_REQALL,str);
		if(byte == CARD_FOUND)
		{
			byte = mfrc522_get_card_serial(str);
			if(byte == CARD_FOUND)
			{
				DIO_WriteChannel(DIO_ChannelA0 ,STD_HIGH);
				UART0_Transmit('@');
				for(byte=0;byte<8;byte++)
				{
					UART0_Transmit(str[byte]);
				}
				UART0_Transmit(';');
			}
		}
	}
}

ISR(USART1_RX_vect)
{
	temp = UDR1_Register;
	esp_buff[esp_buff_len] = temp;
	esp_buff_len++;
	if(esp_buff_len == 100)
		ESP01_ResetBuffer();
	xSemaphoreGiveFromISR(ESP_SEM, NULL);
}