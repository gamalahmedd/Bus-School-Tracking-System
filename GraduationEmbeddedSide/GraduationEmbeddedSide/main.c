#include "HAL/ESP01/ESP01.h"
#include "HAL/MFRC/mfrc522.h"
#include "MCAL/UART/UART.h"
#include "MCAL/SPI/SPI.h"

#define BLUE 	2
#define WHITE 	3

uint8_t byte;
uint8_t str[MAX_LEN];
uint8_t person_recognised = 0;

uint8_t data_recieved = 0;

void intialize_section(void);

int main()
{

	intialize_section();
	
	
	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);
	while(1)
	{
		byte = mfrc522_request(PICC_REQALL,str);
		_delay_ms(100);
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
				_delay_ms(500);
				DIO_WriteChannel(DIO_ChannelA1 ,STD_LOW);
				DIO_WriteChannel(DIO_ChannelA0 ,STD_LOW);
			}
			else if('2' == data_recieved){
				DIO_WriteChannel(DIO_ChannelA2 ,STD_HIGH);
				_delay_ms(500);
				DIO_WriteChannel(DIO_ChannelA2 ,STD_LOW);
				DIO_WriteChannel(DIO_ChannelA0 ,STD_LOW);
				}else{/*Nothing*/}

			}
	}
}

void intialize_section(void){
	SPI_Init();
	UART0_Init();	
	mfrc522_init();
	DIO_ConfigChannel(DIO_ChannelA0 ,OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA1 ,OUTPUT);
	DIO_ConfigChannel(DIO_ChannelA2 ,OUTPUT);

}