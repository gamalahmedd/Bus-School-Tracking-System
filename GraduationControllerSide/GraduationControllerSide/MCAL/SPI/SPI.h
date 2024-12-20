#ifndef SPI_H_
#define SPI_H_
#include "SPI_Registers.h"
#include "SPI_Cfg.h"
#include "BITMATH.h"
#include "STD_TYPES.h"
#include "DIO.h"


void SPI_Init(void);
u_int8 SPI_Master_TransmitChar(u_int8 Data);
u_int8 SPI_Slave_ReceiveChar(u_int8 Data);
void SPI_Master_TransmitString(u_int8* String);
void SPI_Cannel_State(DIO_ChannelTypes ChannelID,SPI_State State);

#endif /* SPI_H_ */