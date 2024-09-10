#include "../../MCAL/EXTI/EXTI.h"
#include "../../Service/service.h"


int main(void)
{
	startScheduler();
}


/*
int main(void)
{
	DIO_ConfigChannel(DIO_ChannelG0, OUTPUT);
	UART0_Init();
	
	u_int8 x = 0;
	while (1)
	{
		x = UART0_Receive();
		if(x == '1')
		{
			DIO_WriteChannel(DIO_ChannelG0, STD_HIGH);
		}
		else if(x == '0')
		{
			DIO_WriteChannel(DIO_ChannelG0, STD_LOW);
		}
	}
}
*/

/*
int main(void)
{
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT4, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT5, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT4, RISING_EDGE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT5, RISING_EDGE);
	Accelerometor_init();
	setActivityParameters();
	setFreeFallParameters();
	GIE_Enable();
	while(1)
	{
		
	}
}
*/