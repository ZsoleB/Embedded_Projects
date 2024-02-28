/*
 * SPI_Driver_Cfg.c
 *
 *  Created on: Sep 18, 2018
 *      Author: zsolt.balo
 */

#include "SPI_Driver_Cfg.h"

SPI_Driver_Setup_Type SPI_CONF_SETUP[SPI_DRIVER_INSTANCE_NUM]=
{
		{
			SPI1,
			DEFAULT,
			DEFAULT,
			DEFAULT,
			DEFAULT,
			DEFAULT,
			DEFAULT,
			SPI_DRIVER_BAUD_RATE_DIV32,
			SPI_DRIVER_CPOL_IDLE_0,
			SPI_DRIVER_CPHA_FIRST_CLOCK_TRANSITION,
			SPI_DRIVER_8_BIT_DATA_FORMAT,
			SPI_DRIVER_MSB_FIRST,
			SPI_DRIVER_MASTER_CONFIGURATION,
			SPI_DRIVER_FULL_DUPLEX,
			OK,
			OK,
			NOK,
			DEFAULT,
			SPI_DRIVER_2_LINE_UNIDIRECTIONAL_DATA_FLOW,
			NOK
		}
};

SPI_Driver_Setup_Type* SPI_SETUP = SPI_CONF_SETUP;