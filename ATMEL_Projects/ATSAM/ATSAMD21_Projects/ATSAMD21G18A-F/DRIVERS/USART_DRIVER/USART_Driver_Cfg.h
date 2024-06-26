/*
 * USART_Driver_Cfg.h
 *
 *  Created on: 9 apr. 2018
 *      Author: Zsole
 */

#ifndef DRIVERS_USART_DRIVER_USART_DRIVER_CFG_H_
#define DRIVERS_USART_DRIVER_USART_DRIVER_CFG_H_

#include "USART_Driver.h"

#define USART_DRIVER_INSTANCE_NUM 					((uint32)0x01)

#define USART_DRIVER_USART0_SELECT					NOK		/*use SERCOM 0 with UART configuration*/
#define USART_DRIVER_USART1_SELECT					NOK		/*use SERCOM 1 with UART configuration*/
#define USART_DRIVER_USART2_SELECT					NOK		/*use SERCOM 2 with UART configuration*/
#define USART_DRIVER_USART3_SELECT					NOK		/*use SERCOM 3 with UART configuration*/
#define USART_DRIVER_USART4_SELECT					NOK		/*use SERCOM 4 with UART configuration*/
#define USART_DRIVER_USART5_SELECT					OK		/*use SERCOM 5 with UART configuration*/
#define USART_DRIVER_DEBUG_CONTROL					NOK		/*Controls the baud-rate generator functionality when the CPU is halted by an external debugger*/

#endif /* DRIVERS_USART_DRIVER_USART_DRIVER_CFG_H_ */
