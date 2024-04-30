#ifndef DIO_CFG_H_
#define DIO_CFG_H_
#include "DIO_Types.h"
#include "BITMATH.h"
#include "DIO_Registers.h"

typedef struct 
{
	DIO_DirectionTypes Direction;
	DIO_PortTypes Port;
	DIO_ChannelTypes Channel;
	DIO_PullUpType PullUp;
}DIO_PinConfig;

extern DIO_PinConfig PinConfig[];
extern const u_int8 countPinsConfigured;

#endif