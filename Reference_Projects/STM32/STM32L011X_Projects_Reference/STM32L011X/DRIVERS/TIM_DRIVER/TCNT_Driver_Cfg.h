/*
 * TCNT_Driver_Cfg.h
 *
 *  Created on: Apr 19, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_TIM_DRIVER_TCNT_DRIVER_CFG_H_
#define DRIVERS_TIM_DRIVER_TCNT_DRIVER_CFG_H_

#include "TCNT_Driver.h"

#define TCNT_DRIVER_TIMER_2                     			OK
#define TCNT_DRIVER_TIMER_21                     			NOK
#define TCNT_DRIVER_LP_TIMER_1                     			NOK
#define TCNT_DRIVER_DIRECTION								TCNT_DRIVER_UP_COUNTER
#define TCNT_DRIVER_INTERRUPT_ENABLE						NOK
#define TCNT_DRIVER_CALLBACK_NUM 							((uint32)0x01)
#define TCNT_DRIVER_INSTANCE_NUM 							((uint32)0x01)

#if(TCNT_DRIVER_INTERRUPT_ENABLE == OK)

#include "NVIC_Driver.h"

#endif
typedef enum {
	TCNT_DRIVER_TIM2
} TCNT_Driver_Instances;

#if(TCNT_DRIVER_INTERRUPT_ENABLE == OK)

typedef enum
{
	TCNT_DRIVER_TIM2_CALLBACK
}TCNT_Driver_Callback_Instances;

TCNT_Driver_callback_type TCNT_Driver_Interrupt_Callbacks[TCNT_DRIVER_CALLBACK_NUM];

void TCNT_Driver_Callback_Function();

#endif

#endif /* DRIVERS_TIM_DRIVER_TCNT_DRIVER_CFG_H_ */
