#ifndef SPI_TYPES_H_
#define SPI_TYPES_H_

#define Dummy_Data 0xFF

typedef enum
{
	SPR0 = 0,
	SPR1,
	CPHA,
	CPOL,
	MSTR,
	DORD,
	SPE,
	SPIE
}SPCR_Bits;

typedef enum
{
	SPI2X = 0,
	WCOL = 6,
	SPIF = 7
}SPSR_Bits;

typedef enum{
	SPI_Slave=0,
	SPI_Master
}SPI_State_Types;

typedef enum{
	SPI_Clock_4=0,
	SPI_Clock_16,
	SPI_Clock_64,
	SPI_Clock_128
}SPI_Clock_Types;

typedef enum{
	SPI_DoubleSpeed_Disable=0,
	SPI_DoubleSpeed_Enable
}SPI_DoubleSpeed_Types;

typedef enum{
	SPI_MSB=0,
	SPI_LSB
}SPI_DataOrder_Types;

typedef enum
{
	SPI_Interrupt_Disable=0,
	SPI_Interrupt_Enable
}SPI_Interrupt_State;

typedef enum
{
	SPI_Disable=0,
	SPI_Enable
}SPI_State;

typedef enum
{
	SPI_Mode0=0,
	SPI_Mode1,
	SPI_Mode2,
	SPI_Mode3,
}SPI_Mode;



#endif