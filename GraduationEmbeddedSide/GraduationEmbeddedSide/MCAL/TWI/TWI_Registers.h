#ifndef TWI_REGISTERS_H_
#define TWI_REGISTERS_H_

/*=================TWI_Registers===============*/
#define TWBR (*(volatile u_int8*)0x70)
#define TWSR (*(volatile u_int8*)0x71)
#define TWAR (*(volatile u_int8*)0x72)
#define TWDR (*(volatile u_int8*)0x73)
#define TWCR (*(volatile u_int8*)0x74)
/*=====================END=====================*/

#endif