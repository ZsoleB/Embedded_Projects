/*
 * USART_Driver.c
 *
 *  Created on: 9 apr. 2018
 *      Author: Zsole
 */

#include "USART_Driver_Cfg.h"

void USART_Driver_Init()
{
	uint16 USART_index = 0x00;

	#if (USART_DRIVER_USART0_SELECT != NOK)
		SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBCMASK |= ((uint32)(0x01<<0x02));
		SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_CLKCTRL = ((uint32)(0x14|(0x01<<0x0E)));

		while(0x00!=(SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_STATUS & ((uint8)(0x01<<0x07))))
		{
			/*Wait until Synchronization is finished*/
		}

	#endif
	
	#if (USART_DRIVER_USART1_SELECT != NOK)
		SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBCMASK |= ((uint32)(0x01<<0x03));
		SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_CLKCTRL = ((uint32)(0x15|(0x01<<0x0E)));

		while(0x00!=(SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_STATUS & ((uint8)(0x01<<0x07))))
		{
			/*Wait until Synchronization is finished*/
		}

	#endif

	#if (USART_DRIVER_USART2_SELECT != NOK)
		SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBCMASK |= ((uint32)(0x01<<0x04));
		SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_CLKCTRL = ((uint32)(0x16|(0x01<<0x0E)));

		while(0x00!=(SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_STATUS & ((uint8)(0x01<<0x07))))
		{
			/*Wait until Synchronization is finished*/
		}

	#endif

	#if (USART_DRIVER_USART3_SELECT != NOK)
		SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBCMASK |= ((uint32)(0x01<<0x05));
		SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_CLKCTRL = ((uint32)(0x17|(0x01<<0x0E)));

		while(0x00!=(SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_STATUS & ((uint8)(0x01<<0x07))))
		{
			/*Wait until Synchronization is finished*/
		}

	#endif

	#if (USART_DRIVER_USART4_SELECT != NOK)
		SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBCMASK |= ((uint32)(0x01<<0x06));
		SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_CLKCTRL = ((uint32)(0x18|(0x01<<0x0E)));

		while(0x00!=(SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_STATUS & ((uint8)(0x01<<0x07))))
		{
			/*Wait until Synchronization is finished*/
		}

	#endif

	#if (USART_DRIVER_USART5_SELECT != NOK)
		SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBCMASK |= ((uint32)(0x01<<0x07));
		SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_CLKCTRL = ((uint32)(0x19|(0x01<<0x0E)));

		while(0x00!=(SYSTEM_GCLK_DRIVER_REG->SYSTEM_GCLK_STATUS & ((uint8)(0x01<<0x07))))
		{
			/*Wait until Synchronization is finished*/
		}

	#endif
	/*
	Some registers are enable-protected, meaning they can only be written when the module is disabled.
	The following registers are enable-protected, meaning they can only be written when the USART is disabled (CTRL.ENABLE=0):
		• Control A register (CTRLA), except the Enable (ENABLE) and Software Reset (SWRST) bits.
		• Control B register (CTRLB), except the Receiver Enable (RXEN) and Transmitter Enable (TXEN) bits.
		• Baud register (BAUD)
	When the USART is enabled or is being enabled (CTRLA.ENABLE=1), any writing attempt to these registers will be 	discarded.
	If the peripheral is being disabled, writing to these registers will be executed after disabling is completed.
	*/

	for(USART_index = 0x00; USART_index<USART_DRIVER_INSTANCE_NUM; USART_index++)
	{
		USART_Driver_Instances eSelectedInstance = USART_SETUP[USART_index].USART_Instance;

		USART_Driver_SWReset(USART_index);

		SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_CTRLB |= USART_SETUP[USART_index].USART_Word_length|
																		(USART_SETUP[USART_index].USART_Stop_bit_select<<0x06)|
																		(USART_SETUP[USART_index].USART_Parity_selection<<0x0D)|
																		(USART_SETUP[USART_index].USART_Transmitter_enable<<0x10)|
																		(USART_SETUP[USART_index].USART_Receiver_enable<<0x11);
                                    

		SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_CTRLA |= (USART_DRIVER_INT_CLOCK)|(USART_DRIVER_ASYNCH_COMM)|
																		(USART_SETUP[USART_index].USART_Oversampling_mode<<0x0D)|
																		(USART_SETUP[USART_index].USART_Driver_TX_PinOut<<0x10)|
																		(USART_SETUP[USART_index].USART_Driver_RX_PinOut<<0x14)|
																		(USART_SETUP[USART_index].USART_Parity_control_enable<<0x18)|
																		(USART_SETUP[USART_index].USART_Payload_Data_Order<<0x1E);

	USART_Driver_Set_Baudrate(USART_index);
    USART_Driver_Start(eSelectedInstance);
	}
}

void  USART_Driver_Set_Baudrate(uint8 USART_setup_nr)
{
	uint32 MANTISA = 0;
	uint8  FRACTION = 0;
	uint32 tmp = 0;
	uint32 result = 0;
	uint8 OperatingMode = 0x00;

  	USART_Driver_Instances eSelectedInstance = USART_SETUP[USART_setup_nr].USART_Instance;

	/*For the Asynchronous Fractional mode the BAUD Register Value Calculation formula was used from the Baud Rate Equation table.

		BAUD = (Fref/S*Fbaud)-FP/8
		Fref - reference frequency (the system frequency in our case)
		S - Sampling rate
		FBaud - Output frequency
		FP - Fractional part (for more precise baud rate values)

	  In the implementation the FP (fractional part is considered 0) which will have an acceptable error margin, 
	  to simplify the calculation.

	  In case a more precise value is neccesary, please change the calculation formula to include also the fractional part. 

	  For the Arithmetic mode the formula bellow,from the Baud Rate Equation table, was applied:

	  	BAUD
	*/

	if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_16X_OVER_SAMPLING_FRACT)
	{
		tmp = ((uint32)(48000000*8))/((uint32)(USART_SETUP[USART_setup_nr].USART_Baudrate*16));
		OperatingMode = 0x00;
	}
	else if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_8X_OVER_SAMPLING_FRACT)
	{
		tmp = ((uint32)(48000000*8))/((uint32)(USART_SETUP[USART_setup_nr].USART_Baudrate*8));
		OperatingMode = 0x00;
	}
	else if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_8X_OVER_SAMPLING_ARITH)
	{
		tmp = 65536 - (((uint32)(65536*8*(USART_SETUP[USART_setup_nr].USART_Baudrate)))/((uint32)(48000000)));
		OperatingMode = 0x01;
	}
	else if(USART_SETUP[USART_setup_nr].USART_Oversampling_mode == USART_DRIVER_16X_OVER_SAMPLING_ARITH)
	{
		tmp = 65536 - (uint16)(((uint32)(65536*16*(USART_SETUP[USART_setup_nr].USART_Baudrate)))/((uint32)(48000000)));
		OperatingMode = 0x01;
	}
	else
	{
		/*Nothing to do here*/
	}

	if(0x00 == OperatingMode)
	{
		MANTISA  = (uint32)((tmp/8) & 0x1FFF);
		FRACTION = (uint8)((tmp%8) & 0x07);

		result = MANTISA|(FRACTION << 0x0D);

		SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_BAUD = result;
	}
	else if(0x01 == OperatingMode)
	{
		SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_BAUD = (uint16)tmp;
	}
	else
	{
		/*Nothing to do here*/
	}
}

uint8 USART_Driver_Receive_Char(USART_Driver_Instances USART_setup_nr)
{
	uint8 Payload=0x00;

  	while((USART_Driver_GetComStatus(USART_setup_nr,USART_DRIVER_FLAG_STATUS_RXC)) == _FAILED_){}
	Payload = (uint8)(SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_DATA);
	return Payload;
}

void USART_Driver_Send_Char(USART_Driver_Instances USART_setup_nr, uint8 data)
{
	while((USART_Driver_GetComStatus(USART_setup_nr,USART_DRIVER_FLAG_STATUS_DRE)) == _FAILED_){}
	SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_DATA = (uint16_t)data;
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
	SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_CTRLA |= USART_DRIVER_ENABLE;

	/*
	Enabling and disabling the SERCOM (CTRLA.ENABLE) requires synchronization. 
	When written, the SYNCBUSY.ENABLE bit will be set until synchronization is complete.	
	*/

	while(0x00 != (SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_SYNCBUSY & USART_DRIVER_SYNCH_ENABLE))
	{
		/*Wait until Synchronization is finished*/
	}
}

void USART_Driver_Stop(uint8 USART_setup_nr)
{
	SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_CTRLA &= (~USART_DRIVER_ENABLE);

	/*
	Enabling and disabling the SERCOM (CTRLA.ENABLE) requires synchronization. 
	When written, the SYNCBUSY.ENABLE bit will be set until synchronization is complete.	
	*/
	while((0x00 != (SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_CTRLA & USART_DRIVER_ENABLE)) ||
		  (0x00 != (SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_SYNCBUSY & USART_DRIVER_SYNCH_ENABLE)))
	{
		/*Wait until Synchronization is finished*/
	}
}

uint8 USART_Driver_GetComStatus(USART_Driver_Instances USART_setup_nr, USART_Driver_ComStatus_bits Status_Bit)
{
	if((SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_INTFLAG & Status_Bit)!=FALSE)
	{
		return _SUCCESS_;
	}
	else
	{
		return _FAILED_;
	}
}

uint8 USART_Driver_GetErrStatus(USART_Driver_Instances USART_setup_nr, USART_Driver_ErrStatus_bits Status_Bit)
{
	if((SERCOM_DRIVER_Registers[USART_setup_nr]->SERCOM_DRIVER_INTFLAG & Status_Bit)!=FALSE)
	{
		return _SUCCESS_;
	}
	else
	{
		return _FAILED_;
	}
}

void USART_Driver_SWReset(USART_Driver_Instances USART_setup_nr)
{
  USART_Driver_Instances eSelectedInstance = USART_SETUP[USART_setup_nr].USART_Instance;

	/*Request SW Reset in order to reset the SERCOM registers*/
	SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_CTRLA |= USART_DRIVER_SWRESET;

	/*
	Wait until the SW reset (bit in the Synch. busy register is set to 0) is finished.
	Due to synchronization, there is a delay from writing CTRLA.SWRST until the reset is complete. CTRLA.SWRST and
	SYNCBUSY.SWRST will both be cleared when the reset is complete.
	*/
	while((0x00 != (SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_CTRLA & USART_DRIVER_SWRESET)) ||
		  (0x00 != (SERCOM_DRIVER_Registers[eSelectedInstance]->SERCOM_DRIVER_SYNCBUSY & USART_DRIVER_SYNCH_SWRST)))
	{
		/*Wait until Synchronization is finished*/
	}
}	