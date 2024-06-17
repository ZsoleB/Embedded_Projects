/*
 * NVIC_Driver.h
 *
 *  Created on: Apr 20, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_
#define DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_

#include "RegMemmap.h"

#define NVIC_DRIVER_AIRCR_VECTORKEY_CLEAR_MASK				((uint32)0xFFFF0000)
#define NVIC_DRIVER_AIRCR_VECTORKEY_MASK					((uint32)0x05FA0000)
#define NVIC_DRIVER_PRIORITY_GROUP_MASK						0x700

/*
Each priority field holds a priority value, 0-192. The lower the value, the greater the priority of the
corresponding interrupt. The processor implements only bits[7:6] of each field, bits[5:0] read as zero
and ignore writes. This means writing 255 to a priority register saves value 192 to the register.

The values defined bellow will have to be shifted to the MSB position to set the configured priotity. 
*/

/*yy00.0000*/
#define NVIC_DRIVER_PRIORITY_192						((uint8)0x03)
/*yx00.0000*/
#define NVIC_DRIVER_PRIORITY_128						((uint8)0x02)
/*xy00.0000*/
#define NVIC_DRIVER_PRIORITY_64						    ((uint8)0x01)
/*xx00.0000*/
#define NVIC_DRIVER_PRIORITY_0                          ((uint8)0x00)

/*Interrupt Number Definition */
typedef enum
{
  /******  Cortex-M0+ Processor Exceptions Numbers ******************************/
  NVIC_DRIVER_CORTM0_NonMaskableInt_IRQn      = -14,/**<  2 Non Maskable Interrupt                 */
  NVIC_DRIVER_CORTM0_HardFault_IRQn           = -13,/**<  3 Cortex-M0+ Hard Fault Interrupt        */
  NVIC_DRIVER_CORTM0_SVCall_IRQn              = -5, /**< 11 Cortex-M0+ SV Call Interrupt           */
  NVIC_DRIVER_CORTM0_PendSV_IRQn              = -2, /**< 14 Cortex-M0+ Pend SV Interrupt           */
  NVIC_DRIVER_CORTM0_SysTick_IRQn             = -1, /**< 15 Cortex-M0+ System Tick Interrupt       */
  /******  SAMD21G18A-specific Interrupt Numbers ***********************/
  NVIC_DRIVER_SAMD_PM_IRQn                  =  0, /**<  0 SAMD21G18A Power Manager (PM) */
  NVIC_DRIVER_SAMD_SYSCTRL_IRQn             =  1, /**<  1 SAMD21G18A System Control (SYSCTRL) */
  NVIC_DRIVER_SAMD_WDT_IRQn                 =  2, /**<  2 SAMD21G18A Watchdog Timer (WDT) */
  NVIC_DRIVER_SAMD_RTC_IRQn                 =  3, /**<  3 SAMD21G18A Real-Time Counter (RTC) */
  NVIC_DRIVER_SAMD_EIC_IRQn                 =  4, /**<  4 SAMD21G18A External Interrupt Controller (EIC) */
  NVIC_DRIVER_SAMD_NVMCTRL_IRQn             =  5, /**<  5 SAMD21G18A Non-Volatile Memory Controller (NVMCTRL) */
  NVIC_DRIVER_SAMD_DMAC_IRQn                =  6, /**<  6 SAMD21G18A Direct Memory Access Controller (DMAC) */
  NVIC_DRIVER_SAMD_USB_IRQn                 =  7, /**<  7 SAMD21G18A Universal Serial Bus (USB) */
  NVIC_DRIVER_SAMD_EVSYS_IRQn               =  8, /**<  8 SAMD21G18A Event System Interface (EVSYS) */
  NVIC_DRIVER_SAMD_SERCOM0_IRQn             =  9, /**<  9 SAMD21G18A Serial Communication Interface 0 (SERCOM0) */
  NVIC_DRIVER_SAMD_SERCOM1_IRQn             = 10, /**< 10 SAMD21G18A Serial Communication Interface 1 (SERCOM1) */
  NVIC_DRIVER_SAMD_SERCOM2_IRQn             = 11, /**< 11 SAMD21G18A Serial Communication Interface 2 (SERCOM2) */
  NVIC_DRIVER_SAMD_SERCOM3_IRQn             = 12, /**< 12 SAMD21G18A Serial Communication Interface 3 (SERCOM3) */
  NVIC_DRIVER_SAMD_SERCOM4_IRQn             = 13, /**< 13 SAMD21G18A Serial Communication Interface 4 (SERCOM4) */
  NVIC_DRIVER_SAMD_SERCOM5_IRQn             = 14, /**< 14 SAMD21G18A Serial Communication Interface 5 (SERCOM5) */
  NVIC_DRIVER_SAMD_TCC0_IRQn                = 15, /**< 15 SAMD21G18A Timer Counter Control 0 (TCC0) */
  NVIC_DRIVER_SAMD_TCC1_IRQn                = 16, /**< 16 SAMD21G18A Timer Counter Control 1 (TCC1) */
  NVIC_DRIVER_SAMD_TCC2_IRQn                = 17, /**< 17 SAMD21G18A Timer Counter Control 2 (TCC2) */
  NVIC_DRIVER_SAMD_TC3_IRQn                 = 18, /**< 18 SAMD21G18A Basic Timer Counter 3 (TC3) */
  NVIC_DRIVER_SAMD_TC4_IRQn                 = 19, /**< 19 SAMD21G18A Basic Timer Counter 4 (TC4) */
  NVIC_DRIVER_SAMD_TC5_IRQn                 = 20, /**< 20 SAMD21G18A Basic Timer Counter 5 (TC5) */
  NVIC_DRIVER_SAMD_ADC_IRQn                 = 23, /**< 23 SAMD21G18A Analog Digital Converter (ADC) */
  NVIC_DRIVER_SAMD_AC_IRQn                  = 24, /**< 24 SAMD21G18A Analog Comparators (AC) */
  NVIC_DRIVER_SAMD_DAC_IRQn                 = 25, /**< 25 SAMD21G18A Digital Analog Converter (DAC) */
  NVIC_DRIVER_SAMD_PTC_IRQn                 = 26, /**< 26 SAMD21G18A Peripheral Touch Controller (PTC) */
  NVIC_DRIVER_SAMD_I2S_IRQn                 = 27, /**< 27 SAMD21G18A Inter-IC Sound Interface (I2S) */
  NVIC_DRIVER_SAMD_PERIPH_COUNT_IRQn        = 28  /**< Number of peripheral IDs */
}NVIC_DRIVER_IRQNUM_Type;

typedef struct
{
	const uint8 NVIC_IRQ_Priority;
    void (*NVIC_IRQ_IRQ_Handler_Fct)(uint8 Preemption_Priority,uint8 Sub_Priority);
}NVIC_DRIVER_Setup_Type;

extern NVIC_DRIVER_Setup_Type* NVIC_SETUP;

void NVIC_Driver_Init();
void NVIC_Driver_SetInterrupt(NVIC_DRIVER_IRQNUM_Type IRQChannel,uint8 Preemption_Priority,uint8 Sub_Priority);
void NVIC_Driver_ClearInterrupt(uint8 IRQChannel);

/*Controller Specific functions*/

void NVIC_Driver_Set_SYSTICK_Interrupt(uint8 Preemption_priority,uint8 Sub_priority);

#endif /* DRIVERS_NVIC_DRIVER_NVIC_DRIVER_H_ */
