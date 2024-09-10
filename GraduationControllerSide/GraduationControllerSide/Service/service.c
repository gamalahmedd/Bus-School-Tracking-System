#include "../../MCAL/EXTI/EXTI.h"
#include "service.h"

char IsItGGAString = 0;

void startScheduler()
{
	_delay_ms(3000);
	System_Init();
	
	ESP_SEM = xSemaphoreCreateCounting(1, 0);
	ACCIDENT_SEM = xSemaphoreCreateCounting(1, 0);
	ACCELERATION_SEM = xSemaphoreCreateCounting(1, 0);
	GPS_SEM = xSemaphoreCreateCounting(1, 0);
	UART1_SEND = xSemaphoreCreateMutex();
	CHECK_CONNECTION = xEventGroupCreate();
	xTaskCreate(ESP01_CheckConnectionTask, "CheckConnection", configMINIMAL_STACK_SIZE, NULL, ESP_PRIORITY, NULL);
	xTaskCreate(GPS_GetLocationTask, "GPSLocation", 500, NULL, GPS_PRIORITY, NULL);
	xTaskCreate(RFID_TakeAttendance, "RFIDAttendance", 200, NULL, RFID_PRIORITY, NULL);
	xTaskCreate(ADXL_SendAccidentAlertTask, "Alert Accident", configMINIMAL_STACK_SIZE, NULL, ADXL_PRIORITY, NULL);
	xTaskCreate(ADXL_SendAccelerationAlertTask, "Acceleration Alert", configMINIMAL_STACK_SIZE, NULL, ADXL_PRIORITY, NULL);
	
	LCD_ClearScreen();
	LCD_SetCursor(1, 1);
	LCD_SendString("Welcome to");
	LCD_SetCursor(2, 1);
	LCD_SendString("Our System!");
	vTaskStartScheduler();
}

void System_Init()
{
	GPS_Init();
	ESP01_Init();
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT4, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT5, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT4, RISING_EDGE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT5, RISING_EDGE);
	DIO_ConfigChannel(DIO_ChannelG0, OUTPUT);
	DIO_ConfigChannel(DIO_ChannelG1, OUTPUT);
	GIE_Enable();
	mfrc522_init();
	Accelerometor_init();
	setActivityParameters();
	setFreeFallParameters();
	LCD_Init();
}

/*-------------------------------------------------------ESP Task--------------------------------------------------------*/

void ESP01_CheckConnectionTask(void *pvParam)
{
	u_int8 ret = 0;
	while(1)
	{
		ret = xSemaphoreTake(ESP_SEM, 100);
		if(ret == 1)
		{
			if(ESP01_CheckConnection() == 3)
			{
				DIO_WriteChannel(DIO_ChannelG0, STD_HIGH);
				xEventGroupSetBits(CHECK_CONNECTION, (GPS_BIT | ADXL_BIT | RFID_BIT));
			}
			else if(ESP01_CheckConnection() == 2)
			{
				DIO_WriteChannel(DIO_ChannelG0, STD_LOW);
				xEventGroupClearBits(CHECK_CONNECTION, (GPS_BIT | ADXL_BIT | RFID_BIT));
			}
		}
		vTaskDelay(80);
	}
}


/*--------------------------------------------------------GPS Task-----------------------------------------------*/
void GPS_GetLocationTask(void *pvParam)
{
	EventBits_t uxBits;
	u_int8 ret = 0;
	u_int8 ret1 = 0;
	while(1)
	{
		uxBits = xEventGroupGetBits(CHECK_CONNECTION);
		if(uxBits & (GPS_BIT | ADXL_BIT | RFID_BIT) == (GPS_BIT | ADXL_BIT | RFID_BIT))
		{
			ret = xSemaphoreTake(GPS_SEM, 10);
			if(ret == 1)
			{
				ret1 = xSemaphoreTake(UART1_SEND, portMAX_DELAY);
				if(ret1 == 1)
				{
					UART1_TransmitString("GPS-");
					get_gpstime();
					UART1_TransmitString(Time_Buffer);
					UART1_TransmitString(",");
					get_latitude(GGA_Pointers[0]);
					UART1_TransmitString(degrees_buffer);
					memset(degrees_buffer, 0, degrees_buffer_size);
					UART1_TransmitString(",");
					get_longitude(GGA_Pointers[2]);
					UART1_TransmitString(degrees_buffer);
					UART1_TransmitString(",");
					memset(degrees_buffer, 0, degrees_buffer_size);
					get_altitude(GGA_Pointers[7]);
					UART1_TransmitString(Altitude_Buffer);
					UART1_TransmitString("GPS");
					xSemaphoreGive(UART1_SEND);
				}
			}
		}
		vTaskDelay(3000);
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
						UART1_TransmitString(str);
						UART1_TransmitString("RFID");
						LCD_ClearScreen();
						LCD_SetCursor(1, 1);
						LCD_SendString("Registered");
						LCD_SetCursor(2, 1);
						LCD_SendString("Successfully!");
						xSemaphoreGive(UART1_SEND);
					}
				}
			}
		}
		vTaskDelay(120);
	}
}
/*-----------------------------------------------ADXL Task------------------------------------------------*/

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
		vTaskDelay(500);
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
		vTaskDelay(600);
	}
}

/*-------------------------------------------ISR Functions----------------------------------*/


ISR(INT4_vect)
{
	xSemaphoreGiveFromISR(ACCIDENT_SEM, NULL);
	TWI_ByteRead(ADXL345_ALTERNATIVE_ADDRESS,ADXL345_REG_INT_SOURCE,&Reg);
}


ISR(INT5_vect)
{
	xSemaphoreGiveFromISR(ACCELERATION_SEM, NULL);
	TWI_ByteRead(ADXL345_ALTERNATIVE_ADDRESS,ADXL345_REG_INT_SOURCE,&Reg);
}



ISR(USART1_RX_vect)
{
	GIE_Disable();
	temp = UDR1_Register;
	esp_buff[esp_buff_len] = temp;
	esp_buff_len++;
	if(esp_buff_len == 100)
		ESP01_ResetBuffer();
	xSemaphoreGiveFromISR(ESP_SEM, NULL);
	GIE_Enable();
}



ISR(USART0_RX_vect)
{
	GIE_Disable();
	received_char = UDR0_Register;
	
	if(received_char == '$')
	{
		GGA_Index = 0;
		CommaCounter = 0;
		IsItGGAString = 0;
	}
	else if (IsItGGAString == 1)
	{
		if(received_char == ',')
		{
			GGA_Pointers[CommaCounter++] = GGA_Index;
		}
		GGA_Buffer[GGA_Index++] = received_char;
	}
	else if (GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A')
	{
		IsItGGAString = 1;
		GGA_CODE[0] = 0;
		GGA_CODE[1] = 0;
		GGA_CODE[2] = 0;
	}
	else
	{
		GGA_CODE[0] = GGA_CODE[1];
		GGA_CODE[1] = GGA_CODE[2];
		GGA_CODE[2] = received_char;
	}
	xSemaphoreGiveFromISR(GPS_SEM, NULL);
	GIE_Enable();
}
