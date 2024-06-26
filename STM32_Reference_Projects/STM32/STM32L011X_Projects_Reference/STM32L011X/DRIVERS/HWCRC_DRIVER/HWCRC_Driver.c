/*
 * HWCRC_Driver.c
 *
 *  Created on: May 7, 2018
 *      Author: zsolt.balo
 */
#include "HWCRC_Driver.h"
#include "HWCRC_Driver_Cfg.h"

uint32 HWCRC_Driver_Calculate_CRC(uint32 data)
{
	CRC->DR = data;
#if(HWCRC_XOR_OUTPUT_DATA_EN == OK)
	return (uint32) ((CRC->DR)^HWCRC_XOR_OUTPUT_VALUE);
#elif(HWCRC_XOR_OUTPUT_DATA_EN == NOK)
	return (uint32) (CRC->DR);
#else
#error "Please configure HWCRC_XOR_OUTPUT_DATA_EN with OK or NOK";
#endif
}

void HWCRC_Driver_Init()
{
#if (HWCRC_DRIVER_ENABLE == OK)
	RCC->AHBENR |= RCC_AHBENR_CRCEN;
#endif

	HWCRC_Driver_Reset();

	CRC->INIT = HWCRC_INIT_VALUE;
	CRC->POL = HWCRC_POLYNOMIAL;
	CRC->CR &= (~((0x01 << 0x07) | (0x03 << 0x05) | (0x03 << 0x03) | (0x01)));
#if(HWCRC_REVERSE_OUTPUT_DATA_EN == OK)
	CRC->CR |= HWCRC_REVERSE_OUTPUT;
#endif
	CRC->CR |= HWCRC_REVERSE_INPUT_DATA|HWCRC_POLYNOMIAL_SIZE;
}

void HWCRC_Driver_Reset()
{
	CRC->CR = 0x01;
}
