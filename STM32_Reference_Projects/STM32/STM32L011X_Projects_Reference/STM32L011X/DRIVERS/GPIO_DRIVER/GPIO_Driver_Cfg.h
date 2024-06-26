/*
 * GPIO_Driver_Cfg.h
 *
 *  Created on: Jan 23, 2018
 *      Author: zsolt.balo
 */
#ifndef GPIO_DRIVER_CFG_H_
#define GPIO_DRIVER_CFG_H_

#include "GPIO_Driver.h"

#define GPIO_DRIVER_GPIOA 				  			OK
#define GPIO_DRIVER_GPIOB 				  			NOK
#define GPIO_DRIVER_GPIOC 				  			NOK
#define GPIO_DRIVER_INSTANCE_NUM 					((uint32)0x01)

typedef enum
{
	GPIO_DRIVER_PORTA,
}GPIO_Driver_Port_Instances;

typedef enum
{
	/*PORT B Pin*/
	GPIO_DRIVER_PORTA_PIN3
}GPIO_Driver_Pin_Instances;

#endif /* GPIO_DRIVER_CFG_STM32L011X_H_ */
