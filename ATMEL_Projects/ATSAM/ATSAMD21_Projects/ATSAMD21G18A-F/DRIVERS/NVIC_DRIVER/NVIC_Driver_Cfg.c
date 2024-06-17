/*
 * NVIC_Driver_Cfg.c
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#include "NVIC_Driver_Cfg.h"

NVIC_DRIVER_Setup_Type NVIC_CONF_SETUP[NVIC_DRIVER_INSTANCE_NUM] =
{
	{
		NVIC_DRIVER_PRIORITY_128,
		NVIC_Driver_Set_SYSTICK_Interrupt
	}
};

NVIC_DRIVER_Setup_Type* NVIC_SETUP = NVIC_CONF_SETUP;