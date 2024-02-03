#ifndef SPI_REGISTERS_H_
#define SPI_REGISTERS_H_
/*=============SPI_Registers============*/
#define SPCR_Register (*(volatile u_int8*)0x2D)
#define SPSR_Register (*(volatile u_int8*)0x2E)
#define SPDR_Register (*(volatile u_int8*)0x2F)
/*=============END============*/
#define SPI_SS_PIN DIO_ChannelB0
#define SPI_SCK_PIN DIO_ChannelB1
#define SPI_MOSI_PIN DIO_ChannelB2
#define SPI_MISO_PIN DIO_ChannelB3

#endif