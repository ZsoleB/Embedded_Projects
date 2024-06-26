/*
 * HWCRC_Driver.h
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_HWCRC_DRIVER_HWCRC_DRIVER_H_
#define DRIVERS_HWCRC_DRIVER_HWCRC_DRIVER_H_

#include "stm32l0xx.h"
#include "StdTypes.h"

/*This bit controls the reversal of the bit order of the output data.*/
#define HWCRC_REVERSE_OUTPUT                  ((uint32)0x01<<0x07)

/*These bits control the reversal of the bit order of the input data.*/
#define HWCRC_BIT_ORDER_NOT_AFFECTED          ((uint32)0x00<<0x05)
#define HWCRC_BIT_REVERSAL_DONE_BY_BYTE       ((uint32)0x01<<0x05)
#define HWCRC_BIT_REVERSAL_DONE_BY_HALF_WORD  ((uint32)0x02<<0x05)
#define HWCRC_BIT_REVERSAL_DONE_BY_WORD       ((uint32)0x03<<0x05)

/*These bits control the size of the polynomial.*/
#define HWCRC_32_BIT_POLYNOMIAL               ((uint32)0x00<<0x03)
#define HWCRC_16_BIT_POLYNOMIAL               ((uint32)0x01<<0x03)
#define HWCRC_8_BIT_POLYNOMIAL                ((uint32)0x02<<0x03)
#define HWCRC_7_BIT_POLYNOMIAL                ((uint32)0x03<<0x03)

/*If the xor-ing of the output is enabled, than the value of the data register will be
 XOR-ed with the value bellow.
 */
#define HWCRC_XOR_OUTPUT_VALUE                ((uint32)0xFFFFFFFF)

uint32 HWCRC_Driver_Calculate_CRC(uint32 data);
void HWCRC_Driver_Init();
void HWCRC_Driver_Reset();

#endif /* DRIVERS_HWCRC_DRIVER_HWCRC_DRIVER_H_ */
