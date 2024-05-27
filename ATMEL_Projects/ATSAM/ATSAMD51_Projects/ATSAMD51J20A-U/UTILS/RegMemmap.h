/*
 * Memmap.h
 *
 * Created: 05/20/2024 12:50:57 PM
 *  Author: EBALOZS4C
 */ 


#ifndef MEMMAP_H_
#define MEMMAP_H_

/*-----------------------------------------GPIO Memmap-----------------------------------------*/
#include "StdTypes.h"

/*
The I/O Pin Controller (PORT) controls the I/O pins of the device. The I/O pins are organized in a series of groups,
collectively referred to as a PORT group. Each PORT group can have up to 32 pins that can be configured and
controlled individually or as a group. Each pin group has its own PORT registers, with a 0x80 address spacing. 
(in total 0x100 per PORT)
*/
typedef struct
{
    volatile uint32 GPIO_DRIVER_DIR;         /*This register allows the user to configure one or more I/O pins as an input or output.*/
    volatile uint32 GPIO_DRIVER_DIRCLR;      /*This register allows the user to set one or more I/O pins as an input.*/
    volatile uint32 GPIO_DRIVER_DIRSET;      /*This register allows the user to set one or more I/O pins as an output.*/
    volatile uint32 GPIO_DRIVER_DIRTGL;      /*This register allows the user to toggle the direction of one or more I/O pins.*/
    volatile uint32 GPIO_DRIVER_OUT;         /*This register sets the data output drive value for the individual I/O pins in the PORT.*/
    volatile uint32 GPIO_DRIVER_OUTCLR;      /*This register allows the user to set one or more output I/O pin drive levels low.*/
    volatile uint32 GPIO_DRIVER_OUTSET;      /*This register allows the user to set one or more output I/O pin drive levels high.*/
    volatile uint32 GPIO_DRIVER_OUTTGL;      /*This register allows the user to toggle the drive level of one or more output I/O pins.*/
    volatile const uint32 GPIO_DRIVER_IN;    /*These bits are set when the corresponding I/O pin input sampler detects a logical high/low level on the input pin.*/
    volatile uint32 GPIO_DRIVER_CTRL;        /*Configures the input sampling functionality of the I/O pin input samplers, for pins configured as inputs.*/
    volatile uint32 GPIO_DRIVER_WRCONFIG;    /*This register is used to configure several pins simultaneously with the same configuration and/or peripheral multiplexing.*/
    volatile uint32 GPIO_DRIVER_EVCTRL;    /*This register is used to configure several pins simultaneously with the same configuration and/or peripheral multiplexing.*/
    volatile uint8 GPIO_DRIVER_PMUX[16];   /*These bits select the peripheral function, if the corresponding PINCFGy.PMUXEN bit is '1'*/
    volatile uint8 GPIO_DRIVER_PINCFG[32];   /*There are up to 32 Pin Configuration registers in each PORT group, one for each I/O line.*/
    volatile const uint8 RESERVED1[0x20];   /*Not used*/
}GPIO_DRIVER_Register_Group;

typedef struct
{
    GPIO_DRIVER_Register_Group PORT_Group[2];   /*Group 0 consists of the PA pins, group 1 is for the PB pins*/
}GPIO_DRIVER_Registers;

/*The PORT is connected to the high-speed bus matrix through an AHB/APB bridge.*/
#define GPIO_DRIVER_PORT_REG        ((GPIO_DRIVER_Registers*)(0x41008000UL))

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
/*-----------------------------------------PWM Memmap-----------------------------------------*/
/*-----------------------------------------RTC Memmap-----------------------------------------*/
/*-----------------------------------------SPI Memmap-----------------------------------------*/
/*-----------------------------------------TWI Memmap-----------------------------------------*/
/*-----------------------------------------SYSTICK Memmap-----------------------------------------*/
/*-----------------------------------------SYSTEM Memmap-----------------------------------------*/
/*-----------------------------------------TIM Memmap-----------------------------------------*/
/*-----------------------------------------USART Memmap-----------------------------------------*/
/*-----------------------------------------USB Memmap-----------------------------------------*/
/*-----------------------------------------WDG Memmap-----------------------------------------*/


#endif /* MEMMAP_H_ */