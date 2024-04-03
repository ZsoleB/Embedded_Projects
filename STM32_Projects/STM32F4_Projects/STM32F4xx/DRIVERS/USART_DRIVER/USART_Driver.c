/*
 * USART_Driver.c
 *
 *  Created on: 9 apr. 2018
 *      Author: Zsole
 */

#include "USART_Driver_Cfg.h"

void USART_Driver_Init()
{
	uint16 index = 0x00;

	#if (USART_DRIVER_USART1_SELECT != NOK)
		RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
	#endif

	#if (USART_DRIVER_USART2_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	#endif

	#if (USART_DRIVER_USART3_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
	#endif

	#if (USART_DRIVER_USART4_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_UART4EN;
	#endif

	#if (USART_DRIVER_USART5_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_UART5EN;
	#endif

	#if (USART_DRIVER_USART6_SELECT != NOK)
		RCC->APB2ENR|=RCC_APB2ENR_USART6EN;
	#endif

	for(index = 0x00; index<USART_DRIVER_INSTANCE_NUM; index++)
	{
		USART_SETUP[index].USART_Instance->CR1 |=(USART_SETUP[index].USART_Word_length)|
														  (USART_SETUP[index].USART_Parity_control_enable)|
					                                      (USART_SETUP[index].USART_Transmitter_enable)|
														  (USART_SETUP[index].USART_Receiver_enable);

		if (USART_SETUP[index].USART_Parity_control_enable == USART_DRIVER_PARITY_CONTROLL_ENABLE)
		{
			USART_SETUP[index].USART_Instance->CR1 |=(USART_SETUP[index].USART_Parity_selection);
		}

		USART_SETUP[index].USART_Instance->CR2 |=(USART_SETUP[index].USART_Stop_bit_select);

		USART_SETUP[index].USART_Instance->CR3 |=(USART_SETUP[index].USART_Half_duplex_selection);

		USART_Driver_Set_Baudrate(index);
	}
}

void  USART_Driver_Set_Baudrate(uint8 USART_setup_nr)
{
	uint16 MANTISA = 0;
	uint8  FRACTION = 0;
	uint32 tmp = 0;
	uint32 working_freq = 0;
	uint32 result = 0;

	if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_OVER16)
	{
		if((USART_SETUP[USART_setup_nr].USART_Instance == USART1)||
		   (USART_SETUP[USART_setup_nr].USART_Instance == USART6))
		{
			working_freq = (uint32)(90000000);
		}
		else
		{
			working_freq = (uint32)(45000000);
		}

		tmp = (((25*(working_freq))/(4*USART_SETUP[USART_setup_nr].USART_Baudrate)));
	}
	else if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_OVER8)
	{
		if((USART_SETUP[USART_setup_nr].USART_Instance == USART1)||
		   (USART_SETUP[USART_setup_nr].USART_Instance == USART6))
		{
			working_freq = (uint32)(90000000);
		}
		else
		{
			working_freq = (uint32)(45000000);
		}

		tmp = (((25*(working_freq))/(2*USART_SETUP[USART_setup_nr].USART_Baudrate)));
	}

	/*	1 - Multiply by 100 in order to shift the fractional number up.
	 	2 - Divide the new number to get the whole part of the number */
	MANTISA = ((tmp/100)<<4);
	/*	3 - Remove the whole part from the temporary number */
	tmp = tmp - ((MANTISA>>4)*100);

	/*4 - Scale the result of the Faction result to the available bit range (((FRACTION*MAX_VALUE_OF_RANGE)+ROUND_UP_VALUE)&MAXIMUM_NUMBER_OF_THE_ORIGINAL_NUMBER)
	  5 - Multiply with the oversampling value, to scale to the available bit range (4 or 3). This means to multiply with 16 or with 8, the maximum available number
	  6 - Add 50 for rounding up
	  7 - divide by 100 to complete the scaling.
	*/

	if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_OVER16)
	{
		FRACTION = ((((tmp*16)+50)/100)&((uint8_t)0x0F));
	}
	else if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_OVER8)
	{
		FRACTION = ((((tmp*8)+50)/100)&((uint8_t)0x07));
	}

	result = MANTISA|FRACTION;

	USART_SETUP[USART_setup_nr].USART_Instance->BRR = result;
}

uint8 USART_Driver_Receive_Char(uint8 USART_setup_nr)
{
	uint8 Payload=0x00;
	while((USART_Driver_GetStatus(USART_setup_nr,USART_Driver_RXNE))==FAILED);
	Payload = USART_SETUP[USART_setup_nr].USART_Instance->DR;
	return Payload;
}

void USART_Driver_Send_Char(uint8 USART_setup_nr,uint8 data)
{
	while((USART_Driver_GetStatus(USART_setup_nr,USART_Driver_TXE))==FAILED);
	USART_SETUP[USART_setup_nr].USART_Instance->DR = data;
}

void USART_Driver_Send_Str(uint8 USART_setup_nr,char* Msg)
{
	uint8 index = 0x00;
	while(Msg[index])
	{
		USART_Driver_Send_Char(USART_setup_nr,Msg[index]);
		index++;
	}
}

void USART_Driver_Start(uint8 USART_setup_nr)
{
	USART_SETUP[USART_setup_nr].USART_Instance->CR1 |= USART_DRIVER_START;
}

void USART_Driver_Stop(uint8 USART_setup_nr)
{
	USART_SETUP[USART_setup_nr].USART_Instance->CR1 &= USART_DRIVER_STOP;
}

uint8 USART_Driver_GetStatus(uint8 USART_setup_nr,uint8 Status_Bit)
{
	if((USART_SETUP[USART_setup_nr].USART_Instance->SR & Status_Bit)!=FALSE)
	{
		return SUCCES;
	}
	else
	{
		return FAILED;
	}
}
