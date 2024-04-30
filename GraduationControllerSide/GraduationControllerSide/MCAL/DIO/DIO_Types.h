#ifndef DIO_TYPES_H_
#define DIO_TYPES_H_
/*=====(Change DIO_Channel in Easy Way)=====*/
#define A0 DIO_ChannelA0
#define A1 DIO_ChannelA1
#define A2 DIO_ChannelA2
#define A3 DIO_ChannelA3
#define A4 DIO_ChannelA4
#define A5 DIO_ChannelA5
#define A6 DIO_ChannelA6
#define A7 DIO_ChannelA7
/*-------------------------*/
#define B0 DIO_ChannelB0
#define B1 DIO_ChannelB1
#define B2 DIO_ChannelB2
#define B3 DIO_ChannelB3
#define B4 DIO_ChannelB4
#define B5 DIO_ChannelB5
#define B6 DIO_ChannelB6
#define B7 DIO_ChannelB7
/*-------------------------*/
#define C0 DIO_ChannelC0
#define C1 DIO_ChannelC1
#define C2 DIO_ChannelC2
#define C3 DIO_ChannelC3
#define C4 DIO_ChannelC4
#define C5 DIO_ChannelC5
#define C6 DIO_ChannelC6
#define C7 DIO_ChannelC7
/*-------------------------*/
#define D0 DIO_ChannelD0
#define D1 DIO_ChannelD1
#define D2 DIO_ChannelD2
#define D3 DIO_ChannelD3
#define D4 DIO_ChannelD4
#define D5 DIO_ChannelD5
#define D6 DIO_ChannelD6
#define D7 DIO_ChannelD7
/*-------------------------*/
#define E0 DIO_ChannelE0
#define E1 DIO_ChannelE1
#define E2 DIO_ChannelE2
#define E3 DIO_ChannelE3
#define E4 DIO_ChannelE4
#define E5 DIO_ChannelE5
#define E6 DIO_ChannelE6
#define E7 DIO_ChannelE7
/*-------------------------*/
#define F0 DIO_ChannelF0
#define F1 DIO_ChannelF1
#define F2 DIO_ChannelF2
#define F3 DIO_ChannelF3
#define F4 DIO_ChannelF4
#define F5 DIO_ChannelF5
#define F6 DIO_ChannelF6
#define F7 DIO_ChannelF7
/*-------------------------*/
#define G0 DIO_ChannelG0
#define G1 DIO_ChannelG1
#define G2 DIO_ChannelG2
#define G3 DIO_ChannelG3
#define G4 DIO_ChannelG4
/*-------------------------*/

typedef enum{
	DIO_ChannelA0 = 0,
	DIO_ChannelA1,
	DIO_ChannelA2,
	DIO_ChannelA3,
	DIO_ChannelA4,
	DIO_ChannelA5,
	DIO_ChannelA6,
	DIO_ChannelA7,
	
	DIO_ChannelB0,
	DIO_ChannelB1,
	DIO_ChannelB2,
	DIO_ChannelB3,
	DIO_ChannelB4,
	DIO_ChannelB5,
	DIO_ChannelB6,
	DIO_ChannelB7,
	
	DIO_ChannelC0,
	DIO_ChannelC1,
	DIO_ChannelC2,
	DIO_ChannelC3,
	DIO_ChannelC4,
	DIO_ChannelC5,
	DIO_ChannelC6,
	DIO_ChannelC7,
	
	DIO_ChannelD0,
	DIO_ChannelD1,
	DIO_ChannelD2,
	DIO_ChannelD3,
	DIO_ChannelD4,
	DIO_ChannelD5,
	DIO_ChannelD6,
	DIO_ChannelD7,
	
	DIO_ChannelE0,
	DIO_ChannelE1,
	DIO_ChannelE2,
	DIO_ChannelE3,
	DIO_ChannelE4,
	DIO_ChannelE5,
	DIO_ChannelE6,
	DIO_ChannelE7,
	
	DIO_ChannelF0,
	DIO_ChannelF1,
	DIO_ChannelF2,
	DIO_ChannelF3,
	DIO_ChannelF4,
	DIO_ChannelF5,
	DIO_ChannelF6,
	DIO_ChannelF7,
	
	DIO_ChannelG0,
	DIO_ChannelG1,
	DIO_ChannelG2,
	DIO_ChannelG3,
	DIO_ChannelG4,
}DIO_ChannelTypes;

typedef enum{
	DIO_PortA = 0,
	DIO_PortB,
	DIO_PortC,
	DIO_PortD,
	DIO_PortE,
	DIO_PortF,
	DIO_PortG,
}DIO_PortTypes;

typedef enum{
	INPUT = 0,
	OUTPUT = 1,
}DIO_DirectionTypes;

typedef enum{
	DISABLE = 0,
	ENABLE,
	EMPTY,
	}DIO_PullUpType;

#endif