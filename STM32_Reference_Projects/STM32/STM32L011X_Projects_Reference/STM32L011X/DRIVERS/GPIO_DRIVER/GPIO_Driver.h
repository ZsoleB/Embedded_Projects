/*
 * GPIO_Driver.h
 *
 *  Created on: Jan 10, 2018
 *      Author: zsolt.balo
 */

#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

#include "stm32l0xx.h"
#include "StdTypes.h"


#define GPIO_DRIVER_MODE_INPUT								((uint8)0x00)
#define GPIO_DRIVER_MODE_GP_OUT								((uint8)0x01)
#define GPIO_DRIVER_MODE_AF									((uint8)0x02)
#define GPIO_DRIVER_MODE_ANALOG								((uint8)0x03)

#define GPIO_DRIVER_OUT_TYPE_PP								((uint8)0x00)
#define GPIO_DRIVER_OUT_TYPE_OD								((uint8)0x01)

#define GPIO_DRIVER_SPEED_LOW								((uint8)0x00)
#define GPIO_DRIVER_SPEED_MEDIUM							((uint8)0x01)
#define GPIO_DRIVER_SPEED_HIGH								((uint8)0x02)
#define GPIO_DRIVER_SPEED_VERY_HIGH							((uint8)0x03)

#define GPIO_DRIVER_PUPD_NO_PUPD							((uint8)0x00)
#define GPIO_DRIVER_PUPD_PU									((uint8)0x01)
#define GPIO_DRIVER_PUPD_PD									((uint8)0x02)

/*AF0: SPI1/USART2/TIM21/EVENTOUT/SYS_AF*/
#define GPIO_DRIVER_AF_OPT_0								((uint8)0x00)
/*AF1: SPI1/I2C1/LPTIM*/
#define GPIO_DRIVER_AF_OPT_1								((uint8)0x01)
/*AF2: LPUART1/LPTIM/TIM2/EVENTOUT/SYS_AF*/
#define GPIO_DRIVER_AF_OPT_2								((uint8)0x02)
/*AF3: I2C1/LPTIM/EVENTOUT*/
#define GPIO_DRIVER_AF_OPT_3								((uint8)0x03)
/*AF4: I2C1/USART2/LPUART1/EVENTOUT*/
#define GPIO_DRIVER_AF_OPT_4								((uint8)0x04)
/*AF5: SPI1/TIM2/21*/
#define GPIO_DRIVER_AF_OPT_5								((uint8)0x05)
/*AF6: LPUART1/EVEVENTOUT*/
#define GPIO_DRIVER_AF_OPT_6								((uint8)0x06)
/*AF7: COMP1/2*/
#define GPIO_DRIVER_AF_OPT_7								((uint8)0x07)


typedef struct
{
	GPIO_TypeDef* GPIO_Port;
	uint16 GPIO_Pin_nr;
	uint16 GPIO_Pins[16];
	uint16 GPIO_Pin_Mode[16];
	uint16 GPIO_Pin_OutputType[16];
	uint16 GPIO_Pin_Speed[16];
	uint16 GPIO_Pin_PuPd[16];
	uint16 GPIO_Pin_Alternate_function[16];
}GPIO_Driver_Setup_Type;

extern GPIO_Driver_Setup_Type* GPIO_SETUP;

void GPIO_Driver_Init();
void GPIO_Driver_SetPin(uint8 GPIO_setup_nr,uint16 Pin);
void GPIO_Driver_ClearPin(uint8 GPIO_setup_nr,uint16 Pin);
uint16 GPIO_Driver_ReadInputData(uint8 GPIO_setup_nr);
uint16 GPIO_Driver_ReadOutputData(uint8 GPIO_setup_nr);
uint8 GPIO_Driver_ReadInputDataBit(uint8 GPIO_setup_nr,uint16 Bit_number);
void GPIO_Driver_Lambda_function();

#endif /* GPIO_DRIVER_H_ */

