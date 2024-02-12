#include "MCAL/UART/UART.h"

int main(void)
{
	UART0_Init();
	UART0_TransmitString("Gamal");
	while(1)
	{
		
	}
}

