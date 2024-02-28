/*
 * DMA_Driver_Cfg.c
 *
 *  Created on: Jan 4, 2019
 *      Author: zsole
 */

#include "DMA_Driver_Cfg.h"

DMA_Driver_Setup_Type DMA_CONF_SETUP[DMA_DRIVER_CHANNEL_INSTANCE_NUM] =
{
	{
			DMA2,
			0x01,
			{DMA2_DRIVER_STREAM_0},
			{DMA_DRIVER_REQ_CHANNEL_0},
			{DMA_DRIVER_CHANNEL_PRIORITY_MEDIUM},
			{DMA_DRIVER_DUBLE_BUFFERING_DISABLE},
			{DMA_DRIVER_MEMORY_BURST_SINGLE_TRANSFER},
			{DMA_DRIVER_PERIPHERAL_BURST_SINGLE_TRANSFER},
			{DMA_DRIVER_NORMAL_MODE},
			{DMA_DRIVER_DIRECT_MODE_DISABLE},
			{DMA_DRIVER_FIFO_THRESHOLD_FULL},
			{DMA_DRIVER_MEMMORY_SIZE_32_BITS},
			{DMA_DRIVER_PERIPHERAL_SIZE_8_BITS},
			{DMA_DRIVER_MEMMORY_INCREMENT_ENABLE},
			{DMA_DRIVER_PERIPHERAL_INCREMENT_ENABLE},
			{DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY},
			{0x04}
	}
};

DMA_Driver_Setup_Type* DMA_SETUP = DMA_CONF_SETUP;


