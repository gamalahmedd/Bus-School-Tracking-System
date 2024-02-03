#ifndef SPI_H_
#define SPI_H_
#include "SPI_Registers.h"
#include "SPI_Cfg.h"
#include "../../LIB/BITMATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"


void SPI_Init(void);
u_int8 SPI_Master_TransmitChar(u_int8 Data);
u_int8 SPI_Slave_ReceiveChar(u_int8 Data);
void SPI_Master_TransmitString(u_int8* String);

#endif /* SPI_H_ */