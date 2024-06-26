#ifndef TWI_TYPES_H_
#define TWI_TYPES_H_

#define TWINT	(7)
#define TWEA	(6)
#define TWSTA	(5)
#define TWSTO	(4)
#define TWEN	(2)
#define TWIE	(0)

typedef enum {
	TW_START=0x08,
	TW_REP_START =0x10,
	TW_MT_SLA_W_ACK =0x18,
	TW_MT_SLA_R_ACK =0x40,
	TW_MT_DATA_ACK  =0x28,
	TW_MR_DATA_ACK  =0x50, // Master received data and send ACK to slave
	TW_MR_DATA_NACK =0x58,
	TW_MT_SLA_W_NACK=0x20,
	TW_MT_DATA_W_NACK=0x30,
	TW_MT_SLA_ARB_LOST=0x38,
	TW_MT_SLA_R_NACK=0x48,
}TWI_States;

typedef enum {
	WRITE=0,
	READ=1
}ADDRESS_Mode;

typedef enum {
	TWI_intDisable = 0x00,
	TWI_intEnable= 0x01,
}TWI_interruptState;

typedef enum {
	TWI_PRESCALE1,
	TWI_PRESCALE4,
	TWI_PRESCALE16,
	TWI_PRESCALE64,
}TWI_Prescaler;

#endif