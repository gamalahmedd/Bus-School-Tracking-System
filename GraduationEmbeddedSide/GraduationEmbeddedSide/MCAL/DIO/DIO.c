#include "DIO.h"

void DIO_Init(void)
{
	u_int8 count;
	DIO_PortTypes PortX;
	DIO_ChannelTypes BitNo;
	
	for(count = A0; count < countPinsConfigured; count++)
	{
		PortX = PinConfig[count].Port;
		BitNo = PinConfig[count].Channel % 8;
		switch(PinConfig[count].Direction)
		{
			case INPUT:
			{
				switch(PortX)
				{
					case DIO_PortA:
					{
						ClearBit(DDRA_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTA_Register, BitNo);
						}
						break;
					}
					case DIO_PortB:
					{
						ClearBit(DDRB_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTB_Register, BitNo);
						}
						break;
					}
					case DIO_PortC:
					{
						ClearBit(DDRC_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTC_Register, BitNo);
						}
						break;
					}
					case DIO_PortD:
					{
						ClearBit(DDRD_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTD_Register, BitNo);
						}
						break;
					}
					case DIO_PortE:
					{
						ClearBit(DDRE_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTE_Register, BitNo);
						}
						break;
					}
					case DIO_PortF:
					{
						ClearBit(DDRF_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTF_Register, BitNo);
						}
						break;
					}
					case DIO_PortG:
					{
						ClearBit(DDRG_Register, BitNo);
						if(PinConfig[count].PullUp == ENABLE)
						{
							SetBit(PORTG_Register, BitNo);
						}
						break;
					}
				}
				break;
			}
			case OUTPUT:
			{
				switch(PortX)
				{
					case DIO_PortA:
					SetBit(DDRA_Register, BitNo);
					break;
					case DIO_PortB:
					SetBit(DDRB_Register, BitNo);
					break;
					case DIO_PortC:
					SetBit(DDRC_Register, BitNo);
					break;
					case DIO_PortD:
					SetBit(DDRD_Register, BitNo);
					break;
					case DIO_PortE:
					SetBit(DDRE_Register, BitNo);
					break;
					case DIO_PortF:
					SetBit(DDRF_Register, BitNo);
					break;
					case DIO_PortG:
					SetBit(DDRG_Register, BitNo);
					break;
				}
				break;
			}
		}
	}
}

void DIO_WriteChannel(DIO_ChannelTypes ChannelID , STD_LevelTypes Level)
{
	DIO_PortTypes PortX = ChannelID / 8;
	DIO_ChannelTypes BitNo = ChannelID % 8;
	switch(Level)
	{
		case STD_LOW:
			switch(PortX)
			{
				case DIO_PortA:
					ClearBit(PORTA_Register, BitNo);
					break;
				case DIO_PortB:
					ClearBit(PORTB_Register, BitNo);
					break;
				case DIO_PortC:
					ClearBit(PORTC_Register, BitNo);
					break;
				case DIO_PortD:
					ClearBit(PORTD_Register, BitNo);
					break;
				case DIO_PortE:
					ClearBit(PORTE_Register, BitNo);
					break;
				case DIO_PortF:
					ClearBit(PORTF_Register, BitNo);
					break;
				case DIO_PortG:
					ClearBit(PORTG_Register, BitNo);
					break;
			}
			break;
		case STD_HIGH:
			switch(PortX)
			{
				case DIO_PortA:
				SetBit(PORTA_Register, BitNo);
				break;
				case DIO_PortB:
				SetBit(PORTB_Register, BitNo);
				break;
				case DIO_PortC:
				SetBit(PORTC_Register, BitNo);
				break;
				case DIO_PortD:
				SetBit(PORTD_Register, BitNo);
				break;
				case DIO_PortE:
				SetBit(PORTE_Register, BitNo);
				break;
				case DIO_PortF:
				SetBit(PORTF_Register, BitNo);
				break;
				case DIO_PortG:
				SetBit(PORTG_Register, BitNo);
				break;
			}
			break;
	}
}

STD_LevelTypes DIO_ReadChannel(DIO_ChannelTypes ChannelID)
{
	DIO_PortTypes PortX = ChannelID / 8;
	DIO_ChannelTypes BitNo = ChannelID % 8;
	STD_LevelTypes Status = STD_LOW;
	switch(PortX)
	{
		case DIO_PortA:
			Status = ReadBit(PINA_Register, BitNo);
			break;
		case DIO_PortB:
			Status = ReadBit(PINB_Register, BitNo);
			break;
		case DIO_PortC:
			Status = ReadBit(PINC_Register, BitNo);
			break;
		case DIO_PortD:
			Status = ReadBit(PIND_Register, BitNo);
			break;
		case DIO_PortE:
			Status = ReadBit(PINE_Register, BitNo);
			break;
		case DIO_PortF:
			Status = ReadBit(PINF_Register, BitNo);
			break;
		case DIO_PortG:
			Status = ReadBit(PING_Register, BitNo);
			break;
	}
	return Status;
}

void DIO_ConfigChannel(DIO_ChannelTypes ChannelID , DIO_DirectionTypes Direction)
{
	DIO_PortTypes PortX = ChannelID / 8;
	DIO_ChannelTypes BitNo = ChannelID % 8;
	switch(Direction)
	{
		case INPUT:
		{
			switch(PortX)
			{
				case DIO_PortA:
					ClearBit(DDRA_Register, BitNo);
					break;
				case DIO_PortB:
					ClearBit(DDRB_Register, BitNo);
					break;
				case DIO_PortC:
					ClearBit(DDRC_Register, BitNo);
					break;
				case DIO_PortD:
					ClearBit(DDRD_Register, BitNo);
					break;
				case DIO_PortE:
					ClearBit(DDRE_Register, BitNo);
					break;
				case DIO_PortF:
					ClearBit(DDRF_Register, BitNo);
					break;
				case DIO_PortG:
					ClearBit(DDRG_Register, BitNo);
					break;
			}
			break;
		}
		case OUTPUT:
		{
			switch(PortX)
			{
				case DIO_PortA:
				SetBit(DDRA_Register, BitNo);
				break;
				case DIO_PortB:
				SetBit(DDRB_Register, BitNo);
				break;
				case DIO_PortC:
				SetBit(DDRC_Register, BitNo);
				break;
				case DIO_PortD:
				SetBit(DDRD_Register, BitNo);
				break;
				case DIO_PortE:
				SetBit(DDRE_Register, BitNo);
				break;
				case DIO_PortF:
				SetBit(DDRF_Register, BitNo);
				break;
				case DIO_PortG:
				SetBit(DDRG_Register, BitNo);
				break;
			}
			break;
		}
			
	}
}

void DIO_ConfigPullUp(DIO_ChannelTypes ChannelID , DIO_PullUpType PullUp)
{
	DIO_PortTypes PortX = ChannelID / 8;
	DIO_ChannelTypes BitNo = ChannelID % 8;
	switch(PullUp)
	{
		case DISABLE:
			switch(PortX)
			{
				case DIO_PortA:
					ClearBit(PORTA_Register, BitNo);
					break;
				case DIO_PortB:
					ClearBit(PORTB_Register, BitNo);
					break;
				case DIO_PortC:
					ClearBit(PORTC_Register, BitNo);
					break;
				case DIO_PortD:
					ClearBit(PORTD_Register, BitNo);
					break;
				case DIO_PortE:
					ClearBit(PORTE_Register, BitNo);
					break;
				case DIO_PortF:
					ClearBit(PORTF_Register, BitNo);
					break;
				case DIO_PortG:
					ClearBit(PORTG_Register, BitNo);
					break;
			}
			break;
		case ENABLE:
			switch(PortX)
			{
				case DIO_PortA:
					SetBit(PORTA_Register, BitNo);
					break;
				case DIO_PortB:
					SetBit(PORTB_Register, BitNo);
					break;
				case DIO_PortC:
					SetBit(PORTC_Register, BitNo);
					break;
				case DIO_PortD:
					SetBit(PORTD_Register, BitNo);
					break;
				case DIO_PortE:
					SetBit(PORTE_Register, BitNo);
					break;
				case DIO_PortF:
					SetBit(PORTF_Register, BitNo);
					break;
				case DIO_PortG:
					SetBit(PORTG_Register, BitNo);
					break;
			}
		break;
	}
}

void DIO_ToggleChannel(DIO_ChannelTypes ChannelID)
{
	DIO_PortTypes PortX = ChannelID / 8;
	DIO_ChannelTypes BitNo = ChannelID % 8;
	switch(PortX)
	{
		case DIO_PortA:
			ToggleBit(PORTA_Register, BitNo);
			break;
		case DIO_PortB:
			ToggleBit(PORTB_Register, BitNo);
			break;
		case DIO_PortC:
			ToggleBit(PORTC_Register, BitNo);
			break;
		case DIO_PortD:
			ToggleBit(PORTD_Register, BitNo);
			break;
		case DIO_PortE:
			ToggleBit(PORTE_Register, BitNo);
			break;
		case DIO_PortF:
			ToggleBit(PORTF_Register, BitNo);
			break;
		case DIO_PortG:
			ToggleBit(PORTG_Register, BitNo);
			break;
	}
}

void DIO_WritePort(DIO_PortTypes PortID,u_int8 PortValue)
{
	switch(PortID)
	{
		case DIO_PortA:
			PORTA_Register = PortValue;
			break;
		case DIO_PortB:
			PORTB_Register = PortValue;
			break;
		case DIO_PortC:
			PORTC_Register = PortValue;
			break;
		case DIO_PortD:
			PORTD_Register = PortValue;
			break;
		case DIO_PortE:
			PORTE_Register = PortValue;
			break;
		case DIO_PortF:
			PORTF_Register = PortValue;
			break;
		case DIO_PortG:
			PORTG_Register = PortValue;
			break;
	}
}

u_int8 DIO_ReadPort(DIO_PortTypes PortID)
{
	u_int8 ReadValue = 0x00;
	switch(PortID)
	{
		case DIO_PortA:
			ReadValue = PORTA_Register;
			break;
		case DIO_PortB:
			ReadValue = PORTB_Register;
			break;
		case DIO_PortC:
			ReadValue = PORTC_Register;
			break;
		case DIO_PortD:
			ReadValue = PORTD_Register;
			break;
		case DIO_PortE:
			ReadValue = PORTE_Register;
			break;
		case DIO_PortF:
			ReadValue = PORTF_Register;
			break;
		case DIO_PortG:
			ReadValue = PORTF_Register;
			break;
	}
	return ReadValue;
}

void DIO_WriteLowNibble(DIO_PortTypes PortID, u_int8 NibbleValue)
{
	NibbleValue &= 0x0F;
	switch(PortID)
	{
		case DIO_PortA:
		{
			PORTA_Register &= 0xF0;
			PORTA_Register |= NibbleValue;
			break;
		}
		case DIO_PortB:
		{
			PORTB_Register &= 0xF0;
			PORTB_Register |= NibbleValue;
			break;
		}
		case DIO_PortC:
		{
			PORTC_Register &= 0xF0;
			PORTC_Register |= NibbleValue;
			break;
		}
		case DIO_PortD:
		{
			PORTD_Register &= 0xF0;
			PORTD_Register |= NibbleValue;
			break;
		}
		case DIO_PortE:
		{
			PORTE_Register &= 0xF0;
			PORTE_Register |= NibbleValue;
			break;
		}
		case DIO_PortF:
		{
			PORTF_Register &= 0xF0;
			PORTF_Register |= NibbleValue;
			break;
		}
		case DIO_PortG:
		{
			PORTG_Register &= 0xF0;
			PORTG_Register |= NibbleValue;
			break;
		}
	}
}

void DIO_WriteHighNibble(DIO_PortTypes PortID, u_int8 NibbleValue)
{
	NibbleValue &= 0xF0;
	switch(PortID)
	{
		case DIO_PortA:
		{
			PORTA_Register &= 0x0F;
			PORTA_Register |= NibbleValue;
			break;
		}
		case DIO_PortB:
		{
			PORTB_Register &= 0x0F;
			PORTB_Register |= NibbleValue;
			break;
		}
		case DIO_PortC:
		{
			PORTC_Register &= 0x0F;
			PORTC_Register |= NibbleValue;
			break;
		}
		case DIO_PortD:
		{
			PORTD_Register &= 0x0F;
			PORTD_Register |= NibbleValue;
			break;
		}
		case DIO_PortE:
		{
			PORTE_Register &= 0x0F;
			PORTE_Register |= NibbleValue;
			break;
		}
		case DIO_PortF:
		{
			PORTF_Register &= 0x0F;
			PORTF_Register |= NibbleValue;
			break;
		}
		case DIO_PortG:
		{
			PORTG_Register &= 0x0F;
			PORTG_Register |= NibbleValue;
			break;
		}
	}
}