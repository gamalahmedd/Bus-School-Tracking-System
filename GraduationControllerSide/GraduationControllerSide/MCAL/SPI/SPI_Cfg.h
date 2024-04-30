#ifndef SPI_CFG_H_
#define SPI_CFG_H_
#include "SPI_Types.h"

typedef struct
{
	SPI_State_Types StateMode;
	SPI_Clock_Types ClockMode;
	SPI_DoubleSpeed_Types DoubleSpeedMode;
	SPI_DataOrder_Types DataOrderMode;
	SPI_Interrupt_State InterruptState;
	SPI_State State;
	SPI_Mode Mode;
}SPI_Init_Types;

extern SPI_Init_Types SPI_CFG;

#endif