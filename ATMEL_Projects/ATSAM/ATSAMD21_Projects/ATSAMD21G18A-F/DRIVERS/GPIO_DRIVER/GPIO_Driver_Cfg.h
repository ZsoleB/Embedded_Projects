/*
 * GPIO_Driver_Cfg.h
 *
 * Created: 05/20/2024 12:58:38 PM
 *  Author: EBALOZS4C
 */ 


#ifndef GPIO_DRIVER_CFG_H_
#define GPIO_DRIVER_CFG_H_

#include "GPIO_Driver.h"

#define GPIO_DRIVER_USE_IOBUS 						NOK
#define GPIO_DRIVER_GPIOA 				  			OK
#define GPIO_DRIVER_GPIOB 				  			NOK
#define GPIO_DRIVER_INSTANCE_NUM 					((uint32)0x01)

typedef enum
{
#if(GPIO_DRIVER_GPIOA == OK)    
	GPIO_DRIVER_PORTA_INST,
#endif
#if(GPIO_DRIVER_GPIOB == OK)
    GPIO_DRIVER_PORTB_INST
#endif
}GPIO_Driver_Config_Instances;

#endif /* GPIO_DRIVER_CFG_H_ */