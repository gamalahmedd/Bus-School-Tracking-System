#ifndef TWI_TYPES_H_
#define TWI_TYPES_H_

typedef enum
{
	TWPS0 = 0,
	TWPS1	
}TWSR_Bits;

typedef enum
{
	TWGCE = 0
}TWAR_Bits;

typedef enum
{
	TWIE = 0,
	TWEN = 2,
	TWWC,
	TWSTO,
	TWSTA,
	TWEA,
	TWINT
}TWCR_Bits;

typedef enum
{
	TWI_Prescaler_1=0,
	TWI_Prescaler_4,
	TWI_Prescaler_16,
	TWI_Prescaler_64
}TWI_Prescaler_Value;

typedef enum
{
	MR_TX_S = 0x08,
	MR_TX_Sr = 0x10,
	MR_TX_SLA_W_ACK = 0x18,
	MR_TX_SLA_W_NACK = 0x20,
	MR_TX_D_ACK = 0x28,
	MR_TX_D_NACK = 0x30,
} Master_Transmit_Mode_Status;

typedef enum
{
	MR_RX_S = 0x08,
	MR_RX_Sr = 0x10,
	MR_RX_SLA_W_ACK = 0x40,
	MR_RX_SLA_W_NACK = 0x48,
	MR_RX_D_ACK = 0x28,
	MR_RX_D_NACK = 0x30,
} Master_Receiver_Mode_Status;

typedef enum
{
	SL_TX_SLA_R_ACK = 0xA8,
	SL_TX_D_ACK = 0xB8,
	SL_TX_D_NACK = 0xC0
} Slave_Transmit_Mode_Status;

typedef enum
{
	SL_RX_SLA_W_ACK = 0x60,
	SL_RX_D_ACK = 0x80,
	SL_TX_D_NACK = 0x88
} Slave_Receiver_Mode_Status;

#endif