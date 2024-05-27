/*
 * GPIO_Driver_Cfg.c
 *
 * Created: 05/20/2024 12:58:28 PM
 *  Author: EBALOZS4C
 */ 

#include "GPIO_Driver_Cfg.h"

GPIO_Driver_Setup_Type GPIO_CONF_SETUP[GPIO_DRIVER_INSTANCE_NUM] =
{
	{
		GPIO_DRIVER_PORTA,
		0x01,
		(const uint8[]){GPIO_DRIVER_PORTA_PIN16},
		(const GPIO_Driver_PinModes[]){GPIO_Driver_PinMode_OUTPUT},
		(const GPIO_Driver_Input_Config[]){GPIO_Driver_Input_Not_Selected},
		(const GPIO_Driver_Output_Config[]){GPIO_Driver_Output_Strong_Drive_Strength},
		(const GPIO_Driver_PinPullUp[]){GPIO_Driver_PinMode_NO_PULL},
		(const GPIO_Driver_PinConfig[]){GPIO_Driver_PF_GPIO}
	},
};

GPIO_Driver_Setup_Type* GPIO_SETUP = GPIO_CONF_SETUP;

void GPIO_Driver_Lambda_function()
{

}