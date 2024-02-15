#include "EXTI.h"
#include <avr/interrupt.h>

void (*EXT_INTERRUPT0_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT1_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT2_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT3_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT4_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT5_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT6_FUNCTION_PTR)(void) = 0;
void (*EXT_INTERRUPT7_FUNCTION_PTR)(void) = 0;

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

void EXT_INTERRUPTS_SetCallBack(EXT_INTERRUPT_Types INTERRUPT_NO,void (*EXT_INTERRUPT_FUNCTION_COPY_PTR)(void))
{
	switch(INTERRUPT_NO)
	{
		case EXT_INTERRUPT0:
			EXT_INTERRUPT0_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT1:
			EXT_INTERRUPT1_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT2:
			EXT_INTERRUPT2_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT3:
			EXT_INTERRUPT3_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT4:
			EXT_INTERRUPT4_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT5:
			EXT_INTERRUPT5_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT6:
			EXT_INTERRUPT6_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
		case EXT_INTERRUPT7:
			EXT_INTERRUPT7_FUNCTION_PTR = EXT_INTERRUPT_FUNCTION_COPY_PTR;
			break;
	}
}

ISR(INT0_vect)
{
	EXT_INTERRUPT0_FUNCTION_PTR();
}

ISR(INT1_vect)
{
	EXT_INTERRUPT1_FUNCTION_PTR();
}

ISR(INT2_vect)
{
	EXT_INTERRUPT2_FUNCTION_PTR();
}

ISR(INT3_vect)
{
	EXT_INTERRUPT3_FUNCTION_PTR();
}

ISR(INT4_vect)
{
	EXT_INTERRUPT4_FUNCTION_PTR();
}

ISR(INT5_vect)
{
	EXT_INTERRUPT5_FUNCTION_PTR();
}

ISR(INT6_vect)
{
	EXT_INTERRUPT6_FUNCTION_PTR();
}

ISR(INT7_vect)
{
	EXT_INTERRUPT7_FUNCTION_PTR();
}