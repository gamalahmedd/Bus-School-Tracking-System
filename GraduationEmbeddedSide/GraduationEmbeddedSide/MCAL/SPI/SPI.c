#include "SPI.h"
#include "../../LIB/Clock.h"

void SPI_Init(void)
{
	switch(SPI_CFG.StateMode)
	{
		case SPI_Master:
			DIO_ConfigChannel(SPI_MOSI_PIN, OUTPUT);
			DIO_ConfigChannel(SPI_SCK_PIN, OUTPUT);
			DIO_ConfigChannel(SPI_SS_PIN, OUTPUT);
			DIO_ConfigChannel(SPI_MISO_PIN, INPUT);
			DIO_WriteChannel(SPI_SS_PIN, STD_HIGH);
			SPCR_Register |= (SPI_CFG.StateMode << MSTR);
			SPSR_Register |= (SPI_CFG.DoubleSpeedMode << SPI2X);
			SPCR_Register |= (SPI_CFG.ClockMode << SPR0);
			SPCR_Register |= (SPI_CFG.DataOrderMode << DORD);
			SPCR_Register |= (SPI_CFG.InterruptState << SPIE);
			SPCR_Register |= (SPI_CFG.Mode << CPHA);
			SPCR_Register |= (SPI_CFG.State << SPE);
			break;
		case SPI_Slave:
			DIO_ConfigChannel(SPI_MOSI_PIN, INPUT);
			DIO_ConfigChannel(SPI_SCK_PIN, INPUT);
			DIO_ConfigChannel(SPI_SS_PIN, INPUT);
			DIO_ConfigChannel(SPI_MISO_PIN, OUTPUT);
			SPCR_Register |= (SPI_CFG.StateMode << MSTR);
			SPSR_Register |= (SPI_CFG.DoubleSpeedMode << SPI2X);
			SPCR_Register |= (SPI_CFG.ClockMode << SPR0);
			SPCR_Register |= (SPI_CFG.DataOrderMode << DORD);
			SPCR_Register |= (SPI_CFG.InterruptState << SPIE);
			SPCR_Register |= (SPI_CFG.Mode << CPHA);
			SPCR_Register |= (SPI_CFG.State << SPE);
			break;
	}
}

u_int8 SPI_Master_TransmitChar(u_int8 Data)
{
	DIO_WriteChannel(SPI_SS_PIN, STD_LOW);
	SPDR_Register = Data;
	while(ReadBit(SPSR_Register, SPIF) == 0);
	return SPDR_Register;
}

u_int8 SPI_Slave_ReceiveChar(u_int8 Data)
{
	SPDR_Register = Data;
	while(ReadBit(SPSR_Register, SPIF) == 0);
	return SPDR_Register;
}

void SPI_Master_TransmitString(u_int8* String)
{
	while((*String) != 0)
	{
		SPI_Master_TransmitChar(*String);
		_delay_ms(150);
		String++;
	}
}