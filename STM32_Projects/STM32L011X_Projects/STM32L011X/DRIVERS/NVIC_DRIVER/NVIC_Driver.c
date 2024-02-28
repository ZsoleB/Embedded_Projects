/*
 * NVIC_Driver.c
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#include "NVIC_Driver_Cfg.h"

void NVIC_Driver_SetInterrupt(IRQn_Type IRQChannel, uint32 priority)
{
	if (IRQChannel < 0)
	{
		SCB->SHP[_SHP_IDX(IRQChannel)] = (SCB->SHP[_SHP_IDX(IRQChannel)]& ~(0xFF << _BIT_SHIFT(IRQChannel)))
				| (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF)<< _BIT_SHIFT(IRQChannel));
	}
	else
	{
		NVIC->IP[_IP_IDX(IRQChannel)] = (NVIC->IP[_IP_IDX(IRQChannel)]& ~(0xFF << _BIT_SHIFT(IRQChannel)))
				| (((priority << (8 - __NVIC_PRIO_BITS)) & 0xFF)<< _BIT_SHIFT(IRQChannel));
	}

    NVIC->ISER[0] = (0x01 << ((uint32)(IRQChannel) & 0x1F));
}

void NVIC_Driver_ClearInterrupt(uint8 IRQChannel)
{
	NVIC->ICER[0] = (0x01 << ((uint32) (IRQChannel) & 0x1F));
}

#if (NVIC_DRIVER_TIMER_INTERRUPT_ENABLE	== OK)

	#include "TCNT_Driver_Cfg.h"

	void NVIC_Driver_SetTimer_Update_Interrupt(uint32 priority)
	{
		#if ((TCNT_DRIVER_TIMER_2)==OK)
			TIM2->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(TIM2_IRQn,priority);
		#endif

		#if ((TCNT_DRIVER_TIMER_21)==OK)
			TIM21->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(TIM21_IRQn,priority);
		#endif

		#if ((TCNT_DRIVER_LP_TIMER_1)==OK)
			LPTIM1->DIER |=(TCNT_DRIVER_UPDATE_GENERATION);
			NVIC_Driver_SetInterrupt(LPTIM1_IRQn,priority);
		#endif

	}

#endif

#if (NVIC_DRIVER_EXTI_INTERRUPT_ENABLE	== OK)
void NVIC_Driver_Set_EXTI_Interrupt(uint32 priority)
{

#if ((defined(NVIC_DRIVER_EXTI_0_FLAG))||(defined(NVIC_DRIVER_EXTI_1_FLAG)))
	NVIC_Driver_SetInterrupt(EXTI0_1_IRQn,priority);
#endif

#if ((defined(NVIC_DRIVER_EXTI_2_FLAG))||(defined(NVIC_DRIVER_EXTI_3_FLAG)))
	NVIC_Driver_SetInterrupt(EXTI2_3_IRQn,priority);
#endif

#if ((defined(NVIC_DRIVER_EXTI_4_FLAG))||(defined(NVIC_DRIVER_EXTI_5_FLAG))||(defined(NVIC_DRIVER_EXTI_6_FLAG)))
	NVIC_Driver_SetInterrupt(EXTI4_15_IRQn,priority);
#endif

#if ((defined(NVIC_DRIVER_EXTI_7_FLAG))||(defined(NVIC_DRIVER_EXTI_8_FLAG))||(defined(NVIC_DRIVER_EXTI_9_FLAG)))
	NVIC_Driver_SetInterrupt(EXTI4_15_IRQn,priority);
#endif

#if ((defined(NVIC_DRIVER_EXTI_10_FLAG))||(defined(NVIC_DRIVER_EXTI_11_FLAG))||(defined(NVIC_DRIVER_EXTI_12_FLAG)))
	NVIC_Driver_SetInterrupt(EXTI4_15_IRQn,priority);
#endif

#if ((defined(NVIC_DRIVER_EXTI_13_FLAG))||(defined(NVIC_DRIVER_EXTI_14_FLAG))||(defined(NVIC_DRIVER_EXTI_15_FLAG)))
	NVIC_Driver_SetInterrupt(EXTI4_15_IRQn,priority);
#endif

}
#endif

#if (NVIC_DRIVER_SYSTICK_INTERRUPT_ENABLE == OK)
	void NVIC_Driver_Set_SYSTICK_Interrupt(uint32 priority)
	{
		/*Enable the Systick interrupt */
		SysTick->CTRL|=(0x01<<0x01);
		NVIC_Driver_SetInterrupt(SysTick_IRQn,priority);
	}
#endif

#if(NVIC_DRIVER_RTC_INTERRUPT_ENABLE == OK)
	void NVIC_Driver_Set_RTC_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{
		#if(NVIC_RTC_OVERFLOW_INTERRUPT_FLAG == OK)
			/*Enable overflow interrupt*/
			RTC->CRH |= RTC_DRIVER_OVERFLOW_INTERRUPT_ENABLE;
			NVIC_Driver_SetInterrupt(RTC_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if(NVIC_RTC_ALARM_INTERRUPT_FLAG == OK)
			/*Enable alarm interrupt*/
			RTC->CRH |= RTC_DRIVER_ALARM_INTERRUPT_ENABLE;
			NVIC_Driver_SetInterrupt(RTC_IRQn,Preemption_priority,Sub_priority);
		#endif

		#if(NVIC_RTC_SECOND_INTERRUPT_FLAG == OK)
			/*Enable second interrupt*/
			RTC->CRH |= RTC_DRIVER_SECOND_INTERRUPT_ENABLE;
			NVIC_Driver_SetInterrupt(RTC_IRQn,Preemption_priority,Sub_priority);
		#endif
	}
#endif

#if (NVIC_DRIVER_WWDT_INTERRUPT_ENABLE == OK)

	#include "WWDT_Driver_cfg.h"

	void NVIC_Driver_Set_WWDT_Interrupt(uint8 Preemption_priority,uint8 Sub_priority)
	{
		/*Enable the WWDT interrupt */
		WWDG->CFR|= WWDT_DRIVER_INTERRUPT_ENABLE;
		NVIC_Driver_SetInterrupt(WWDG_IRQn,Preemption_priority,Sub_priority);
	}
#endif
