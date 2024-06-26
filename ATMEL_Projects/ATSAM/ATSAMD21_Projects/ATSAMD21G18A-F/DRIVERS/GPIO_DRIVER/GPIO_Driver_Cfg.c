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
	  GPIO_DRIVER_PORTB,
	  0x02,
	  (const uint8[]){GPIO_DRIVER_PORTB_PIN22,GPIO_DRIVER_PORTB_PIN23},
	  (const GPIO_Driver_PinModes[]){GPIO_Driver_PinMode_INPUT,GPIO_Driver_PinMode_INPUT},
	  (const GPIO_Driver_Input_Config[]){GPIO_Driver_Input_Not_Selected,GPIO_Driver_Input_Not_Selected},
	  (const GPIO_Driver_Output_Config[]){GPIO_Driver_Output_Strong_Drive_Strength,GPIO_Driver_Output_Strong_Drive_Strength},
	  (const GPIO_Driver_PinPullUp[]){GPIO_Driver_PinMode_NO_PULL,GPIO_Driver_PinMode_NO_PULL},
	  (const GPIO_Driver_PinConfig[]){GPIO_Driver_PF_SERCOM_ALT,GPIO_Driver_PF_SERCOM_ALT}
	},
};

GPIO_Driver_Setup_Type* GPIO_SETUP = GPIO_CONF_SETUP;

void GPIO_Driver_Lambda_function()
{

}