/*
 * NVIC_Driver.c
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#include "NVIC_Driver_Cfg.h"

void NVIC_Driver_Init()
{
	uint8 uIRQ_index = 0x00;
	uint8 uConf_Priority = 0x00;

	for(uIRQ_index = 0x00;uIRQ_index<NVIC_DRIVER_INSTANCE_NUM;++uIRQ_index)
	{
		uConf_Priority = NVIC_SETUP[uIRQ_index].NVIC_IRQ_Priority;
		NVIC_SETUP[uIRQ_index].NVIC_IRQ_IRQ_Handler_Fct(uConf_Priority,0x00);
	}
}

void NVIC_Driver_SetInterrupt(NVIC_DRIVER_IRQNUM_Type IRQChannel, uint8 Preemption_Priority,uint8 Sub_Priority)
{
	uint32 uPreviousConfig = 0x00;
	uint32 uNewConfig = 0x00;

	/*Cortex-M0 doesn't have the group-subgroup implementation, so this argument can be ignored*/
	_UNUSED_(Sub_Priority);
	
	/*According to the datahseet:
		Find the IPR number and byte offset for interrupt N as follows:
			• The corresponding IPR number, M, is given by M = N DIV 4
			• The byte offset of the required Priority field in this register is N MOD 4, where:
				– byte offset 0 refers to register bits[7:0]
				– byte offset 1 refers to register bits[15:8]
				– byte offset 2 refers to register bits[23:16]
				– byte offset 3 refers to register bits[31:24].

		In order to reduce code size, the DIV 4 will be changed to >>2 and MOD4 to &0x03.
		To calculate the offset needed for the IRQ priority the NMOD4 result will be shifted by 3 (multiply by 8 to jump to the correct byte).  			
	*/

	/*Configure the IRQ priority*/
	if(((int32)IRQChannel)<0)
	{
		/*Store the other IRQ configurations and delete the configuration for this IRQ*/
		uPreviousConfig = SYSTEM_SCB_DRIVER_REG->SYSTEM_SCB_SHP[(((((uint32)(int32)(IRQChannel))&0x0F)-8)>>0x02)] & (~(0xFF<<((((uint32)(int32)(IRQChannel)) & 0x03UL)<<0x03UL)));

		/*Create the new priority for the selected IRQ.*/
		uNewConfig = uPreviousConfig | (((Preemption_Priority << 0x06UL) && (uint32)0xFFUL)<<((((uint32)(int32)(IRQChannel)) & 0x03UL)<<0x03UL));

		/* Set Priority for Cortex-M  System Interrupts */
		SYSTEM_SCB_DRIVER_REG->SYSTEM_SCB_SHP[(((((uint32)(int32)(IRQChannel))&0x0F)-8)>>0x02)] = uNewConfig;
	}
	else
	{
		/*Store the other IRQ configurations and delete the configuration for this IRQ*/
		uPreviousConfig = SYSTEM_NVIC_DRIVER_REG->SYSTEM_NVIC_IP[(((uint32)(IRQChannel))>>0x02)] & (~(0xFF<<((((uint32)(IRQChannel)) & 0x03UL)<<0x03UL)));

		/*Create the new priority for the selected IRQ.*/
		uNewConfig = uPreviousConfig | (((Preemption_Priority<<0x06UL) && (uint32)0xFFUL)<<((((uint32)(IRQChannel)) & 0x03UL)<<0x03UL));

		/*Set interrupt priority for the NVIC*/
		SYSTEM_NVIC_DRIVER_REG->SYSTEM_NVIC_IP[(((uint32)(IRQChannel))>>0x02)] = uNewConfig;
	}

	/*Enable the interrupt.*/
    SYSTEM_NVIC_DRIVER_REG->SYSTEM_NVIC_ISER = (uint32)(0x01 << (IRQChannel & (uint8_t)0x1F));
}

void NVIC_Driver_ClearInterrupt(uint8 IRQChannel)
{
	/*Clear the requested IRQ*/
	SYSTEM_NVIC_DRIVER_REG->SYSTEM_NVIC_ICER = (uint32)(0x01 << (IRQChannel & (uint8_t)0x1F));
}

#if (NVIC_DRIVER_SYSTICK_INTERRUPT_ENABLE == OK)
void NVIC_Driver_Set_SYSTICK_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
{
		/*Enable the Systick interrupt */
		SYSTEM_SYSTICK_DRIVER_REG->SYSTEM_SYSTICK_CSR|=(0x01<<0x01);
		NVIC_Driver_SetInterrupt(NVIC_DRIVER_CORTM0_SysTick_IRQn,Preemption_priority,Sub_priority);
}
#endif


