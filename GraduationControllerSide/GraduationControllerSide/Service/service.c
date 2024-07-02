#include "service.h"


void startScheduler()
{
	System_Init();
	
	ESP_SEM = xSemaphoreCreateCounting(1, 0);
	ACCIDENT_SEM = xSemaphoreCreateCounting(1, 0);
	ACCELERATION_SEM = xSemaphoreCreateCounting(1, 0);
	UART1_SEND = xSemaphoreCreateMutex();
	CHECK_CONNECTION = xEventGroupCreate();
	xTaskCreate(ESP01_CheckConnectionTask, "CheckConnection", configMINIMAL_STACK_SIZE, NULL, ESP_PRIORITY, NULL);
	xTaskCreate(GPS_GetLocationTask, "GPSLocation", 200, NULL, GPS_PRIORITY, NULL);
	xTaskCreate(RFID_TakeAttendance, "RFIDAttendance", 200, NULL, RFID_PRIORITY, NULL);
	xTaskCreate(ADXL_SendAccidentAlertTask, "Alert Accident", configMINIMAL_STACK_SIZE, NULL, ADXL_PRIORITY, NULL);
	xTaskCreate(ADXL_SendAccelerationAlertTask, "Acceleration Alert", configMINIMAL_STACK_SIZE, NULL, ADXL_PRIORITY, NULL);
	
	vTaskStartScheduler();
}

void System_Init()
{
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT4, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT5, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT4, RISING_EDGE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT5, RISING_EDGE);
	GIE_Enable();
	ESP01_Init();
	DIO_ConfigChannel(DIO_ChannelG0, OUTPUT);
	DIO_ConfigPullUp(DIO_ChannelG0, DISABLE);
	DIO_ConfigChannel(DIO_ChannelG1, OUTPUT);
	DIO_ConfigPullUp(DIO_ChannelG1, DISABLE);
	GPS_Init();
	LCD_Init();
	mfrc522_init();
	Accelerometor_init();
	setActivityParameters();
	setFreeFallParameters();
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
				DIO_WriteChannel(DIO_ChannelG0, STD_HIGH);
				xEventGroupSetBits(CHECK_CONNECTION, (GPS_BIT | ADXL_BIT | RFID_BIT));
			}
			else
			{
				DIO_WriteChannel(DIO_ChannelG0, STD_LOW);
				xEventGroupClearBits(CHECK_CONNECTION, (GPS_BIT | ADXL_BIT | RFID_BIT));
			}
		}
		vTaskDelay(30);
	}
	
}


/*--------------------------------------------------------GPS Task-----------------------------------------------*/

void GPS_GetLocationTask(void *pvParam)
{
	char longitude[15];
	char latitude[15];
	EventBits_t uxBits;
	u_int8 ret = 0;
	while(1)
	{
		uxBits = xEventGroupGetBits(CHECK_CONNECTION);
		if(uxBits & (GPS_BIT | ADXL_BIT | RFID_BIT) == (GPS_BIT | ADXL_BIT | RFID_BIT))
		{
			getGPSLocation();
			if(find_string(gps_buff, "$GPRMC") == 1)
			{
				memset(longitude, 0, 15);
				memset(latitude, 0, 15);
				find_get_string(gps_buff, "$GPGLL,", 7, ",", 0, latitude);
				find_get_string(gps_buff, latitude, 14, ",", 0, longitude);
				GPS_Buffer_Reset();
				ret = xSemaphoreTake(UART1_SEND, portMAX_DELAY);
				if(ret == 1)
				{
					UART1_TransmitString("GPS-");
					UART1_TransmitString(latitude);
					UART1_TransmitString(",");
					UART1_TransmitString(longitude);
					UART1_TransmitString("GPS");
					xSemaphoreGive(UART1_SEND);
				}
			}
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
	EventBits_t uxBits;
	u_int8 ret = 0;
	while(1)
	{
		uxBits = xEventGroupGetBits(CHECK_CONNECTION);
		if(uxBits & (GPS_BIT | ADXL_BIT | RFID_BIT) == (GPS_BIT | ADXL_BIT | RFID_BIT))
		{
			
			DIO_WriteChannel(DIO_ChannelG1, STD_LOW);
			byte = mfrc522_request(PICC_REQALL,str);
			if(byte == CARD_FOUND)
			{
				byte = mfrc522_get_card_serial(str);
				if(byte == CARD_FOUND)
				{
					ret = xSemaphoreTake(UART1_SEND, portMAX_DELAY);
					if(ret == 1)
					{
						DIO_WriteChannel(DIO_ChannelG1 ,STD_HIGH);
						UART1_TransmitString("RFID-");
						UART1_TransmitString(byte);
						UART1_TransmitString("RFID");
						xSemaphoreGive(UART1_SEND);
					}
				}
			}
		}
		vTaskDelay(200);
	}
}

/*-----------------------------------------------ADXL Task--------------------------------------*/
void ADXL_SendAccidentAlertTask(void *pvParam)
{
	u_int8 ret = 0;
	u_int8 ret1 = 0;
	EventBits_t uxBits;
	while (1)
	{
		uxBits = xEventGroupGetBits(CHECK_CONNECTION);
		if(uxBits & (GPS_BIT | ADXL_BIT | RFID_BIT) == (GPS_BIT | ADXL_BIT | RFID_BIT))
		{
			ret = xSemaphoreTake(ACCIDENT_SEM, 10);
			if(ret == 1)
			{
				ret1 = xSemaphoreTake(UART1_SEND, portMAX_DELAY);
				if(ret1 == 1)
				{
					UART1_TransmitString("ADXL-AccidentADXL");
					xSemaphoreGive(UART1_SEND);
				}
			}
		}
		vTaskDelay(50);
	}
}

void ADXL_SendAccelerationAlertTask(void *pvParam)
{
	u_int8 ret = 0;
	u_int8 ret1 = 0;
	EventBits_t uxBits;
	while(1)
	{
		uxBits = xEventGroupGetBits(CHECK_CONNECTION);
		if(uxBits & (GPS_BIT | ADXL_BIT | RFID_BIT) == (GPS_BIT | ADXL_BIT | RFID_BIT))
		{
			ret = xSemaphoreTake(ACCELERATION_SEM, 10);
			if(ret == 1)
			{
				ret1 = xSemaphoreTake(UART1_SEND, portMAX_DELAY);
				if(ret1 == 1)
				{
					UART1_TransmitString("ADXL-AccelerationADXL");
					xSemaphoreGive(UART1_SEND);
				}
			}
		}
		vTaskDelay(60);
	}
}

/*-------------------------------------------ISR Functions----------------------------------*/

void INT4_Function()
{
	xSemaphoreGiveFromISR(ACCIDENT_SEM, NULL);
	TWI_ByteRead(ADXL345_ALTERNATIVE_ADDRESS,ADXL345_REG_INT_SOURCE,&Reg);
}

void INT5_Function()
{
	xSemaphoreGiveFromISR(ACCELERATION_SEM, NULL);
	TWI_ByteRead(ADXL345_ALTERNATIVE_ADDRESS,ADXL345_REG_INT_SOURCE,&Reg);
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