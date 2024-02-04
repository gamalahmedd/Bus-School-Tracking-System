#ifndef TWI_CFG_H_
#define TWI_CFG_H_
#include "../../LIB/Clock.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BITMATH.h"
#include "TWI_Registers.h"
#include "TWI_Types.h"


#define MasterStartCondition ((1 << TWINT) | (1 << TWEN) | (1 << TWSTA))
#define MasterStopCondition ((1 << TWINT) | (1 << TWEN) | (1 << TWSTO))
#define MasterSend_DataAddress ((1 << TWINT) | (1 << TWEN))
#define SendACK ((1 << TWINT) | (1 << TWEN) | (1 << TWEA))
#define ReceiveACK ((1 << TWINT) | (1 << TWEN) | (1 << TWEA))
#define SendNACK ((1 << TWINT) | (1 << TWEN))



#endif