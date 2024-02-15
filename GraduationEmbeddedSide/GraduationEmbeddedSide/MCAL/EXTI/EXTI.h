#ifndef EXTI_H_
#define EXTI_H_
#include "EXTI_Registers.h"
#include "EXTI_Types.h"
#include "../../LIB/BITMATH.h"

void EXT_INTERRUPTS_STATE(EXT_INTERRUPT_Types INTERRUPT_NO,EXT_INTERRUPT_STATE_Types STATE);
void EXT_INTERRUPTS_SNCONTROL_MODE(EXT_INTERRUPT_Types INTERRUPT_NO,SNC_MODE_Types MODE);
void EXT_INTERRUPTS_SetCallBack(EXT_INTERRUPT_Types INTERRUPT_NO,void (*EXT_INTERRUPT_FUNCTION_COPY_PTR)(void));

#endif