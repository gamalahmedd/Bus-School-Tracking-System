#include "services.h"



void intialize_section(void);

TaskHandle_t RFID_task_Handel = NULL;

TaskHandle_t GPS_task_Handel = NULL;

TaskHandle_t ADXL_task_Handel = NULL;


/*-------------------------------------------RFID TASK---------------------------------------------------------------*/
void RFID_task(void *ptr)
{
	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);
	
	while(1)
	{
		byte = mfrc522_request(PICC_REQALL,str);
		vTaskDelay(100);
		if(byte == CARD_FOUND)
		{
			byte = mfrc522_get_card_serial(str);
			if(byte == CARD_FOUND)
			{
				DIO_WriteChannel(DIO_ChannelA0 ,STD_HIGH);
				person_recognised = 1;
				UART0_Transmit('@');
				for(byte=0;byte<8;byte++){
					UART0_Transmit(str[byte]);
				}
				UART0_Transmit(';');
			}

		}
		if(1 == person_recognised){
			person_recognised = 0;
			data_recieved = UART0_Receive();
			if('1' == data_recieved){
				DIO_WriteChannel(DIO_ChannelA1 ,STD_HIGH);
				vTaskDelay(500);
				DIO_WriteChannel(DIO_ChannelA1 ,STD_LOW);
				DIO_WriteChannel(DIO_ChannelA0 ,STD_LOW);
			}
			else if('2' == data_recieved){
				DIO_WriteChannel(DIO_ChannelA2 ,STD_HIGH);
				vTaskDelay(500);
				DIO_WriteChannel(DIO_ChannelA2 ,STD_LOW);
				DIO_WriteChannel(DIO_ChannelA0 ,STD_LOW);
				}else{/*Nothing*/}

			}
	}
}


/*--------------------------------------------------------------------------------------------------------------------*/


/*-----------------------------------------------GPS TASK---------------------------------------------------------------*/

void GPS_task(void *ptr)
{
	
	while(1)
	{
		
	}
}

/*------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------ADXL TASK---------------------------------------------------------------*/
void ADXL_task(void *ptr)
{
	
	while(1)
	{
		
	}
}


/*-------------------------------------------------------------------------------------------------------------------------*/
void startScheduler(void)
{
	
	intialize_section();
	
	
	xTaskCreate(RFID_task ,"RFID_task" ,200 ,(void*) 0 ,RFID_PRIORITY ,&RFID_task_Handel);
	
	xTaskCreate(GPS_task ,"GPS_task" ,200 ,(void*) 0 ,GPS_PRIORITY ,&GPS_task_Handel);
	
	xTaskCreate(ADXL_task ,"ADXL_task" ,200 ,(void*) 0 ,ADXL_PRIORITY ,&ADXL_task_Handel);

	
	
	
	
	vTaskStartScheduler();
}


void intialize_section(void){
	SPI_Init();
	UART0_Init();
	mfrc522_init();
	DIO_ConfigChannel(DIO_ChannelA0 ,OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA1 ,OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA2 ,OUTPUT);

}