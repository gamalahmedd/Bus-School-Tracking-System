#include "HAL/ESP01/ESP01.h"
#include "HAL/MFRC/mfrc522.h"
#include "MCAL/UART/UART.h"
#include "MCAL/SPI/SPI.h"

#define BLUE 	2
#define WHITE 	3

uint8_t byte;
uint8_t str[MAX_LEN];

void intialize_section(void);

int main()
{
	ESP01_Init();
	intialize_section();
	
	
	byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg,byte|0x20);
	byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg,byte|0x80);
	while(1)
	{
		if(ESP01_CheckConnection())
		{
			byte = mfrc522_request(PICC_REQALL,str);
			_delay_ms(100);
			if(byte == CARD_FOUND)
			{
				byte = mfrc522_get_card_serial(str);
				if(byte == CARD_FOUND)
				{
					UART1_Transmit('@');
					for(byte=0;byte<8;byte++)
					{
						UART1_Transmit(str[byte]);
					}
					UART1_Transmit(';');
				}

			}
		}
	}
}

void intialize_section(void){
	SPI_Init();
	UART1_Init();	
	mfrc522_init();
}