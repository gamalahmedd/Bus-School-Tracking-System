#include "EXTI.h"

void EXT_INTERRUPTS_STATE(EXT_INTERRUPT_Types INTERRUPT_NO,EXT_INTERRUPT_STATE_Types STATE)
{
	switch(STATE)
	{
		case EXT_INTERRUPT_ENABLE:
		{
			switch(INTERRUPT_NO)
			{
				case EXT_INTERRUPT0:
					SetBit(EIMSK_Register, INT0);
					break;
				case EXT_INTERRUPT1:
					SetBit(EIMSK_Register, INT1);
					break;
				case EXT_INTERRUPT2:
					SetBit(EIMSK_Register, INT2);
					break;
				case EXT_INTERRUPT3:
					SetBit(EIMSK_Register, INT3);
					break;
				case EXT_INTERRUPT4:
					SetBit(EIMSK_Register, INT4);
					break;
				case EXT_INTERRUPT5:
					SetBit(EIMSK_Register, INT5);
					break;
				case EXT_INTERRUPT6:
					SetBit(EIMSK_Register, INT6);
					break;
				case EXT_INTERRUPT7:
					SetBit(EIMSK_Register, INT7);
					break;
			}
			break;
		}
		case EXT_INTERRUPT_DISABLE:
		{
			switch(INTERRUPT_NO)
			{
				case EXT_INTERRUPT0:
					ClearBit(EIMSK_Register, INT0);
					break;
				case EXT_INTERRUPT1:
					ClearBit(EIMSK_Register, INT1);
					break;
				case EXT_INTERRUPT2:
					ClearBit(EIMSK_Register, INT2);
					break;
				case EXT_INTERRUPT3:
					ClearBit(EIMSK_Register, INT3);
					break;
				case EXT_INTERRUPT4:
					ClearBit(EIMSK_Register, INT4);
					break;
				case EXT_INTERRUPT5:
					ClearBit(EIMSK_Register, INT5);
					break;
				case EXT_INTERRUPT6:
					ClearBit(EIMSK_Register, INT6);
					break;
				case EXT_INTERRUPT7:
					ClearBit(EIMSK_Register, INT7);
					break;
			}
			break;
		}
	}
}

void EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT_Types INTERRUPT_NO,SNC_MODE_Types MODE)
{
	switch(INTERRUPT_NO)
	{
		case EXT_INTERRUPT0:
			EICRA_Register |= (MODE << ISC00);
			break;
		case EXT_INTERRUPT1:
			EICRA_Register |= (MODE << ISC10);
			break;
		case EXT_INTERRUPT2:
			EICRA_Register |= (MODE << ISC20);
			break;
		case EXT_INTERRUPT3:
			EICRA_Register |= (MODE << ISC30);
			break;
		case EXT_INTERRUPT4:
			EICRB_Register |= (MODE << ISC40);
			break;
		case EXT_INTERRUPT5:
			EICRB_Register |= (MODE << ISC50);
			break;
		case EXT_INTERRUPT6:
			EICRB_Register |= (MODE << ISC60);
			break;
		case EXT_INTERRUPT7:
			EICRB_Register |= (MODE << ISC70);
			break;
	}
}