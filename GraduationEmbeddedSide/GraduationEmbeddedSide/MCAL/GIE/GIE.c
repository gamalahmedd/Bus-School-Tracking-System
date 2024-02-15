#include "GIE.h"

void GIE_Disable(void)
{
	ClearBit(GIE_SREG, GIE_SREG_IBIT);
}

void GIE_Enable(void)
{
	SetBit(GIE_SREG, GIE_SREG_IBIT);
}