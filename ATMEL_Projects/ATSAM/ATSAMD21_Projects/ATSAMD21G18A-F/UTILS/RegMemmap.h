/*
 * Memmap.h
 *
 * Created: 05/20/2024 12:50:57 PM
 *  Author: EBALOZS4C
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

#include "StdTypes.h"
/*-----------------------------------------GPIO Memmap-----------------------------------------*/

/*
The IO Pin Controller (PORT) controls the I/O pins of the device. The I/O pins are organized in a series of groups,
collectively referred to as a PORT group. Each PORT group can have up to 32 pins that can be configured and
controlled individually or as a group. Each pin group has its own PORT registers, with a 0x80 address spacing. 
(in total 0x100 per PORT)
*/
typedef struct
{
    volatile uint32 GPIO_DRIVER_DIR;            /*This register allows the user to configure one or more I/O pins as an input or output.*/
    volatile uint32 GPIO_DRIVER_DIRCLR;         /*This register allows the user to set one or more I/O pins as an input.*/
    volatile uint32 GPIO_DRIVER_DIRSET;         /*This register allows the user to set one or more I/O pins as an output.*/
    volatile uint32 GPIO_DRIVER_DIRTGL;         /*This register allows the user to toggle the direction of one or more I/O pins.*/
    volatile uint32 GPIO_DRIVER_OUT;            /*This register sets the data output drive value for the individual I/O pins in the PORT.*/
    volatile uint32 GPIO_DRIVER_OUTCLR;         /*This register allows the user to set one or more output I/O pin drive levels low.*/
    volatile uint32 GPIO_DRIVER_OUTSET;         /*This register allows the user to set one or more output I/O pin drive levels high.*/
    volatile uint32 GPIO_DRIVER_OUTTGL;         /*This register allows the user to toggle the drive level of one or more output I/O pins.*/
    volatile const uint32 GPIO_DRIVER_IN;       /*These bits are set when the corresponding I/O pin input sampler detects a logical high/low level on the input pin.*/
    volatile uint32 GPIO_DRIVER_CTRL;           /*Configures the input sampling functionality of the I/O pin input samplers, for pins configured as inputs.*/
    volatile uint32 GPIO_DRIVER_WRCONFIG;       /*This register is used to configure several pins simultaneously with the same configuration and peripheral multiplexing.*/
    volatile const uint8 RESERVED0[0x04];       /*Not used*/
    volatile uint8 GPIO_DRIVER_PMUX[0x10];        /*These bits select the peripheral function, if the corresponding PINCFGy.PMUXEN bit is '1'*/
    volatile uint8 GPIO_DRIVER_PINCFG[0x20];      /*There are up to 32 Pin Configuration registers in each PORT group, one for each I/O line.*/
    volatile const uint8 RESERVED1[0x20];       /*Not used*/
}GPIO_DRIVER_Register_Group;

typedef struct
{
    GPIO_DRIVER_Register_Group PORT_Group[2];   /*Group 0 consists of the PA pins, group 1 is for the PB pins*/
}GPIO_DRIVER_Registers;

/*The PORT is connected to the high-speed bus matrix through an AHB/APB bridge.*/
#define GPIO_DRIVER_PORT_REG        ((GPIO_DRIVER_Registers*)(0x41004400UL))
/*The PORT is connected to the low-latency CPU local bus (IOBUS; ARM single-cycle I/O port).*/
#define GPIO_DRIVER_PORT_IOBUS_REG  ((GPIO_DRIVER_Registers*)(0x60000000UL)) 

/*-----------------------------------------ADC Memmap-----------------------------------------*/
/*-----------------------------------------DAC Memmap-----------------------------------------*/
/*-----------------------------------------CAN Memmap-----------------------------------------*/
/*-----------------------------------------DMA Memmap-----------------------------------------*/
/*-----------------------------------------EXTI Memmap-----------------------------------------*/
/*-----------------------------------------FLASH Memmap-----------------------------------------*/
/*-----------------------------------------HWCRC Memmap-----------------------------------------*/
/*-----------------------------------------HWENCODER Memmap-----------------------------------------*/
/*-----------------------------------------LIN Memmap-----------------------------------------*/
/*-----------------------------------------NVIC Memmap-----------------------------------------*/
typedef struct
{
	volatile uint32 SYSTEM_NVIC_ISER;           	/*Interrupt Set Enable Register */
    volatile const uint32 RESERVED0[31U];           /*Not used*/
	volatile uint32 SYSTEM_NVIC_ICER;           	/*Interrupt Clear Enable Register */
	volatile const uint32 RSERVED1[31U];            /*Not used*/
	volatile uint32 SYSTEM_NVIC_ISPR;           	/*Interrupt Set Pending Register */
	volatile const uint32 RESERVED2[31U];           /*Not used*/
	volatile uint32 SYSTEM_NVIC_ICPR;           	/*Interrupt Clear Pending Register */
	volatile const uint32 RESERVED3[31U];           /*Not used*/
	volatile const uint32 RESERVED4[64U];           /*Not used*/
	volatile uint32 SYSTEM_NVIC_IP[8U];             /*Interrupt Priority Register */
}SYSTEM_NVIC_Register_Group;

/*Registers specific for the ARM Cortex-M0+ processor, based on the ARMv6 Architecture (SCB, NVIC, SYSTICK)*/
#define SYSTEM_NVIC_DRIVER_REG          ((SYSTEM_NVIC_Register_Group*)(0xE000E100UL))

/*-----------------------------------------PWM Memmap-----------------------------------------*/
/*-----------------------------------------RTC Memmap-----------------------------------------*/
/*-----------------------------------------SPI Memmap-----------------------------------------*/
/*-----------------------------------------TWI Memmap-----------------------------------------*/
/*-----------------------------------------SYSTICK Memmap-----------------------------------------*/
typedef struct
{
  volatile uint32 SYSTEM_SYSTICK_CSR;              	/*SysTick Control and Status Register */
  volatile uint32 SYSTEM_SYSTICK_RVR;              	/*SysTick Reload Value Register */
  volatile uint32 SYSTEM_SYSTICK_CVR;               /*SysTick Current Value Register */
  volatile const uint32 SYSTEM_SYSTICK_CALIB;       /*SysTick Calibration Register */
}SYSTEM_SysTick_Register_Group;

/*Registers specific for the ARM Cortex-M0+ processor, based on the ARMv6 Architecture (SCB, NVIC, SYSTICK)*/
#define SYSTEM_SYSTICK_DRIVER_REG       ((SYSTEM_SysTick_Register_Group*)(0xE000E010UL))

/*-----------------------------------------SYSTEM Memmap-----------------------------------------*/
typedef struct
{
    volatile uint8 SYSTEM_PM_CTRL;                  /*Control (not bits to use)*/
    volatile uint8 SYSTEM_PM_SLEEP;                 /*These bits select the Idle mode configuration after a WFI instruction.*/
    volatile const uint8 RESERVED0[0x06];           /*Not used*/
    volatile uint8 SYSTEM_PM_CPUSEL;                /*These bits define the division ratio of the main clock prescaler (2^n).*/
    volatile uint8 SYSTEM_PM_APBASEL;               /*These bits define the division ratio of the APBA clock prescaler (2^n).*/
    volatile uint8 SYSTEM_PM_APBBSEL;               /*These bits define the division ratio of the APBB clock prescaler (2^n).*/
    volatile uint8 SYSTEM_PM_APBCSEL;               /*These bits define the division ratio of the APBC clock prescaler (2^n).*/
    volatile const uint8 RESERVED1[0x08];           /*Not used*/
    volatile uint32 SYSTEM_PM_AHBMASK;              /*Clock masks for AHB peripherals: USB, DMAC, NVMCTRL, DSU, HPB2, HPB1, HPB0*/
    volatile uint32 SYSTEM_PM_APBAMASK;             /*Clock masks for APBA peripherals: EIC, RTC, WDT, GCLK, SYSCTRL, PM, PAC0*/
    volatile uint32 SYSTEM_PM_APBBMASK;             /*Clock masks for APBB peripherals: USB, DMAC, PORT, NVMCTRL, DSU, PAC1*/
    volatile uint32 SYSTEM_PM_APBCMASK;             /*Clock masks for APBC peripherals: TCC3, AC1, I2S, PTC, DAC, AC, ADC, TC7, TC6, TC5, TC4, TC3, TCC2, TCC1, TCC0, SERCOM5, SERCOM4, SERCOM3, SERCOM2, SERCOM1, SERCOM0, EVSYS, PAC2*/
    volatile const uint8 RESERVED2[0x10];           /*Not used*/    
    volatile uint8 SYSTEM_PM_INTENCLR;              /*Interrupt Enable Clear*/
    volatile uint8 SYSTEM_PM_INTENSET;              /*Interrupt Enable Set*/
    volatile uint8 SYSTEM_PM_INTFLAG;               /*Interrupt Flag Status and Clear*/
    volatile const uint8 RESERVED3;                 /*Not used*/
    volatile const uint8 SYSTEM_PM_RCAUSE;          /*Reset Cause bit_6-SYST, bit_5-WDT, bit_4-EXT, bit_2-BOD33, bit_1-BOD12, bit_0-POR*/
}SYSTEM_PM_Register_Group;

typedef struct
{
    volatile uint8 SYSTEM_GCLK_CTRL;                /*Control register*/
    volatile const uint8 SYSTEM_GCLK_STATUS;        /*Status register*/
    volatile uint16 SYSTEM_GCLK_CLKCTRL;             /*Generic Clock Control*/
    volatile uint32 SYSTEM_GCLK_GENCTRL;             /*Generic Clock Generator Control*/
    volatile uint32 SYSTEM_GCLK_GENDIV;              /*Generic Clock Generator Division*/
}SYSTEM_GCLK_Register_Group;

typedef struct
{
	volatile const uint32 SYSTEM_SCB_CPUID;         /*CPUID Base Register */
	volatile uint32 SYSTEM_SCB_ICSR;                /*Interrupt Control and State Register */
    volatile const uint32 RESERVED;                	/*Not used*/
	volatile uint32 SYSTEM_SCB_AIRCR;               /*Application Interrupt and Reset Control Register */
	volatile uint32 SYSTEM_SCB_SCR;                 /*System Control Register */
	volatile uint32 SYSTEM_SCB_CCR;                 /*Configuration Control Register */
	volatile const uint32 RESERVED1;                /*Not used*/
	volatile uint32 SYSTEM_SCB_SHP[2U];             /*System Handlers Priority Registers. [0] is RESERVED */
}SYSTEM_SCB_Register_Group;

/*The Power Manager (PM) controls the reset, clock generation and sleep modes of the device.*/
#define SYSTEM_PM_DRIVER_REG            ((SYSTEM_PM_Register_Group*)(0x40000400UL))
/*Registers specific for the ARM Cortex-M0+ processor, based on the ARMv6 Architecture (SCB, NVIC, SYSTICK)*/
#define SYSTEM_SCB_DRIVER_REG           ((SYSTEM_SCB_Register_Group*)(0xE000ED00UL))
#define SYSTEM_GCLK_DRIVER_REG          ((SYSTEM_GCLK_Register_Group*)(0x40000C00UL))

/*-----------------------------------------TIM Memmap-----------------------------------------*/
/*-----------------------------------------USART Memmap-----------------------------------------*/
typedef struct
{
    volatile uint32 SERCOM_DRIVER_CTRLA;                /*Control register A*/
    volatile uint32 SERCOM_DRIVER_CTRLB;                /*Control register B*/
    volatile const uint8 RESERVED0[0x04];               /*Not used*/
    volatile uint16 SERCOM_DRIVER_BAUD;                 /*BAUD rate*/
    volatile uint8 SERCOM_DRIVER_RXPL;                  /*These bits control the minimum pulse length that is required for a pulse to be accepted by the IrDA receiver*/
    volatile const uint8 RESERVED1[0x05];               /*Not used*/
    volatile uint8 SERCOM_DRIVER_INTENCLR;              /*Interrupt Enable Clear*/
    volatile const uint8 RESERVED2;                     /*Not used*/
    volatile uint8 SERCOM_DRIVER_INTENSET;              /*Interrupt Enable Set*/
    volatile const uint8 RESERVED3;                     /*Not used*/
    volatile uint8 SERCOM_DRIVER_INTFLAG;               /*Interrupt Flag Status and Clear*/
    volatile const uint8 RESERVED4;                     /*Not used*/
    volatile uint16 SERCOM_DRIVER_STATUS;               /*Status register*/
    volatile const uint32 SERCOM_DRIVER_SYNCBUSY;       /*Syncronization busy register (related flags: CTRLB,ENABLE,SWRST)*/
    volatile const uint8 RESERVED5[0x08];               /*Not used*/
    volatile uint16 SERCOM_DRIVER_DATA;                 /*Buffer used to send and store the Serial data*/
    volatile const uint8 RESERVED6[0x05];               /*Not used*/
    volatile uint8 SERCOM_DRIVER_DBGCTRL;               /*Debug Stop Mode, halted when the CPU is halted or continues normal operation.*/
}SERCOM_DRIVER_Register_Group;

/*There are up to six instances of the serial communication interface (SERCOM) peripheral.
A SERCOM can be configured to support a number of modes: I2C, SPI, and USART. When an instance of SERCOM
is configured and enabled, all of the resources of that SERCOM instance will be dedicated to the selected mode.*/
#define SERCOM_0_DRIVER_REG                ((SERCOM_DRIVER_Register_Group*)(0x42000800UL))
#define SERCOM_1_DRIVER_REG                ((SERCOM_DRIVER_Register_Group*)(0x42000C00UL))
#define SERCOM_2_DRIVER_REG                ((SERCOM_DRIVER_Register_Group*)(0x42001000UL))
#define SERCOM_3_DRIVER_REG                ((SERCOM_DRIVER_Register_Group*)(0x42001400UL))
#define SERCOM_4_DRIVER_REG                ((SERCOM_DRIVER_Register_Group*)(0x42001800UL))
#define SERCOM_5_DRIVER_REG                ((SERCOM_DRIVER_Register_Group*)(0x42001C00UL))

/*-----------------------------------------USB Memmap-----------------------------------------*/
/*-----------------------------------------WDG Memmap-----------------------------------------*/


#endif /* MEMMAP_H_ */