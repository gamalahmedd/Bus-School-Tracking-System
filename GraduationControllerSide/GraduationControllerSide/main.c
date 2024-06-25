#include "../../Service/service.h"

//ADXL345_Data TestData;
//u_int8 val;

//void INT4_Function(void);
//void INT5_Function(void);

void main()
{
	startScheduler();
}


/*ADXL345
void main(void)
{
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT4, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_STATE(EXT_INTERRUPT5, EXT_INTERRUPT_ENABLE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT4, RISING_EDGE);
	EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT5, RISING_EDGE);
	EXT_INTERRUPTS_SetCallBack(EXT_INTERRUPT4, INT4_Function);
	EXT_INTERRUPTS_SetCallBack(EXT_INTERRUPT5, INT5_Function);
	GIE_Enable();
	UART1_Init();
	UART1_TransmitString("Hello");
	TWI_Init(I2C_PRESCALE4, I2C_intDisable, 400000, 0x07);
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	setActivityParameters(ADXL345_ALTERNATIVE_ADDRESS, 2 ,ADXL345_INT2);
	setFreeFallParameters(ADXL345_ALTERNATIVE_ADDRESS,0.6,0.08,ADXL345_INT1);
	while(1)
	{
		
		Accelerometor_ReadAxis(ADXL345_ALTERNATIVE_ADDRESS,&TestData);
		UART1_TransmitString("X = ");
		float read1_int = TestData.X_Axis * (float)0.004 * 9.80665F;
		char read1[MAX];
		int len = snprintf(NULL, 0, "%f", read1_int);
		snprintf(read1, len + 1, "%f", read1_int);
		UART1_Transmit(read1);
		UART1_TransmitString("        Y = ");
		float read2_int = TestData.Y_Axis * (float)0.004 * 9.80665F;
		char read2[MAX];
		int len1 = snprintf(NULL, 0, "%f", read2_int);
		snprintf(read2, len1 + 1, "%f", read2_int);
		UART1_Transmit(read2);
		UART1_TransmitString("                    Z = ");
		float read3_int = TestData.Z_Axis * (float)0.004 * 9.80665F;
		char read3[MAX];
		int len2 = snprintf(NULL, 0, "%f", read3_int);
		snprintf(read3, len2 + 1, "%f", read3_int);
		UART1_Transmit(read3);
		_delay_ms(250);
	}
}
*/
/*
void INT4_Function(void)
{
	 UART1_TransmitString("           Free Fall!");
}

void INT5_Function(void)
{
	UART1_TransmitString("            Acceleration Increased!");
}
*/