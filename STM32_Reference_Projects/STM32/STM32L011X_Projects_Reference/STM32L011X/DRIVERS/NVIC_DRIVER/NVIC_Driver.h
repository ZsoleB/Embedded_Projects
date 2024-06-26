/*
 * NVIC_Driver.h
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_
#define DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_


#include "stm32l0xx.h"
#include "StdTypes.h"

void NVIC_Driver_SetInterrupt(IRQn_Type IRQChannel, uint32 priority);
void NVIC_Driver_ClearInterrupt(uint8 IRQChannel);

/*Driver Specific functions*/

void NVIC_Driver_SetTimer_Update_Interrupt(uint32 priority);
void NVIC_Driver_Set_EXTI_Interrupt(uint32 priority);
void NVIC_Driver_Set_SYSTICK_Interrupt(uint32 priority);
void NVIC_Driver_Set_RTC_Interrupt(uint32 priority);
void NVIC_Driver_Set_WWDT_Interrupt(uint32 priority);

#endif /* DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_ */
