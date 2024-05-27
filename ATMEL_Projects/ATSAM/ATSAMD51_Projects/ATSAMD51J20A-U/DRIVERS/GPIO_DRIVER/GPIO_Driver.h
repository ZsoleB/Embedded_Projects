/*
 * GPIO_Driver.h
 *
 * Created: 05/20/2024 12:58:06 PM
 *  Author: EBALOZS4C
 */ 


#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "RegMemmap.h"

#define GPIO_DRIVER_OUTPUT_MODE 							((uint8)0x01)
#define GPIO_DRIVER_INPUT_MODE 								((uint8)0x00)
#define GPIO_DRIVER_CONTINOUS_SAMPLING						((uint8)0x01)
#define GPIO_DRIVER_ON_DEMAND_SAMPLING						((uint8)0x00)
/*
	The DRVSTR bit in ATSAMD21 microcontrollers is used to control the drive strength
	of I/O pins. Setting this bit enables the pin to provide higher current, which is
	useful for driving larger loads or achieving faster switching speeds.
*/
#define GPIO_DRIVER_DRVSTR_STRONG 							((uint8)0x01) 
#define GPIO_DRIVER_DRVSTR_NORMAL 							((uint8)0x00)
#define GPIO_DRIVER_PULL_EN									((uint8)0x01)
#define GPIO_DRIVER_INPUT_EN								((uint8)0x01)
#define GPIO_DRIVER_PMUX_EN									((uint8)0x01)
/*These bits define the event action the PORT will perform on event input x.*/
/*There are up to four input event pins for each PORT group. Each byte of this register addresses one
Event input pin.*/
#define GPIO_DRIVER_PEI_EN									((uint8)0x01)
#define GPIO_DRIVER_PEI_ACT_OUT								((uint8)0x00)
#define GPIO_DRIVER_PEI_ACT_SET								((uint8)0x01)
#define GPIO_DRIVER_PEI_ACT_CLR								((uint8)0x02)
#define GPIO_DRIVER_PEI_ACT_TGL								((uint8)0x03)
#define GPIO_DRIVER_TOGGLE_DIRETION							((uint8)0x01)
#define GPIO_DRIVER_PMUX_PF_A								((uint8)0x00)
#define GPIO_DRIVER_PMUX_PF_B								((uint8)0x01)
#define GPIO_DRIVER_PMUX_PF_C								((uint8)0x02)
#define GPIO_DRIVER_PMUX_PF_D								((uint8)0x03)
#define GPIO_DRIVER_PMUX_PF_E								((uint8)0x04)
#define GPIO_DRIVER_PMUX_PF_F								((uint8)0x05)
#define GPIO_DRIVER_PMUX_PF_G								((uint8)0x06)
#define GPIO_DRIVER_PMUX_PF_H								((uint8)0x07)
#define GPIO_DRIVER_PMUX_PF_I								((uint8)0x08)

typedef enum
{
	GPIO_DRIVER_PORTA,
	GPIO_DRIVER_PORTB
}GPIO_Driver_Instances;

typedef enum
{
	GPIO_DRIVER_PORTA_PIN0,
	GPIO_DRIVER_PORTA_PIN1,
	GPIO_DRIVER_PORTA_PIN2,
	GPIO_DRIVER_PORTA_PIN3,
	GPIO_DRIVER_PORTA_PIN4,
	GPIO_DRIVER_PORTA_PIN5,
	GPIO_DRIVER_PORTA_PIN6,
	GPIO_DRIVER_PORTA_PIN7,
	GPIO_DRIVER_PORTA_PIN8,
	GPIO_DRIVER_PORTA_PIN9,
	GPIO_DRIVER_PORTA_PIN10,
	GPIO_DRIVER_PORTA_PIN11,
	GPIO_DRIVER_PORTA_PIN12,
	GPIO_DRIVER_PORTA_PIN13,
	GPIO_DRIVER_PORTA_PIN14,
	GPIO_DRIVER_PORTA_PIN15,
	GPIO_DRIVER_PORTA_PIN16,
	GPIO_DRIVER_PORTA_PIN17,
	GPIO_DRIVER_PORTA_PIN18,
	GPIO_DRIVER_PORTA_PIN19,
	GPIO_DRIVER_PORTA_PIN20,
	GPIO_DRIVER_PORTA_PIN21,
	GPIO_DRIVER_PORTA_PIN22,
	GPIO_DRIVER_PORTA_PIN23,
	GPIO_DRIVER_PORTA_PIN24,
	GPIO_DRIVER_PORTA_PIN25,
	GPIO_DRIVER_PORTA_PIN26,
	GPIO_DRIVER_PORTA_PIN27,
	GPIO_DRIVER_PORTA_PIN28,
	GPIO_DRIVER_PORTA_PIN29,
	GPIO_DRIVER_PORTA_PIN30,
	GPIO_DRIVER_PORTA_PIN31
}GPIO_Driver_PORTA_Pin_Instances;

typedef enum
{
	GPIO_DRIVER_PORTB_PIN0,
	GPIO_DRIVER_PORTB_PIN1,
	GPIO_DRIVER_PORTB_PIN2,
	GPIO_DRIVER_PORTB_PIN3,
	GPIO_DRIVER_PORTB_PIN4,
	GPIO_DRIVER_PORTB_PIN5,
	GPIO_DRIVER_PORTB_PIN6,
	GPIO_DRIVER_PORTB_PIN7,
	GPIO_DRIVER_PORTB_PIN8,
	GPIO_DRIVER_PORTB_PIN9,
	GPIO_DRIVER_PORTB_PIN10,
	GPIO_DRIVER_PORTB_PIN11,
	GPIO_DRIVER_PORTB_PIN12,
	GPIO_DRIVER_PORTB_PIN13,
	GPIO_DRIVER_PORTB_PIN14,
	GPIO_DRIVER_PORTB_PIN15,
	GPIO_DRIVER_PORTB_PIN16,
	GPIO_DRIVER_PORTB_PIN17,
	GPIO_DRIVER_PORTB_PIN18,
	GPIO_DRIVER_PORTB_PIN19,
	GPIO_DRIVER_PORTB_PIN20,
	GPIO_DRIVER_PORTB_PIN21,
	GPIO_DRIVER_PORTB_PIN22,
	GPIO_DRIVER_PORTB_PIN23,
	GPIO_DRIVER_PORTB_PIN24,
	GPIO_DRIVER_PORTB_PIN25,
	GPIO_DRIVER_PORTB_PIN26,
	GPIO_DRIVER_PORTB_PIN27,
	GPIO_DRIVER_PORTB_PIN28,
	GPIO_DRIVER_PORTB_PIN29,
	GPIO_DRIVER_PORTB_PIN30,
	GPIO_DRIVER_PORTB_PIN31
}GPIO_Driver_PORTB_Pin_Instances;

typedef enum
{
	GPIO_Driver_PinMode_INPUT,	/*Default value*/
	GPIO_Driver_PinMode_OUTPUT
}GPIO_Driver_PinModes;

typedef enum
{
	GPIO_Driver_PinMode_NO_PULL,
	GPIO_Driver_PinMode_PULLUP,
	GPIO_Driver_PinMode_PULLDOWN	/*Default value*/
}GPIO_Driver_PinPullUp;

typedef enum
{
	GPIO_Driver_Input_Not_Selected,
	GPIO_Driver_Input_Sampling_ON_DEMAND,	/*Default value*/
	GPIO_Driver_Input_Sampling_CONTINUOUS
}GPIO_Driver_Input_Config;

typedef enum
{
	GPIO_Driver_Output_Not_Selected,
	GPIO_Driver_Output_Normal_Drive_Strength,	/*Default value*/
	GPIO_Driver_Output_Strong_Drive_Strength
}GPIO_Driver_Output_Config;

typedef enum
{
	GPIO_Driver_PF_GPIO,			/*no peripheral functions selected.*/
	GPIO_Driver_PF_EXTINT,			/*peripheral functions A External interrupts.*/
	GPIO_Driver_PF_ANALOG,			/*peripheral functions B Analog input.*/
	GPIO_Driver_PF_SERCOM,			/*peripheral functions C UART.*/
	GPIO_Driver_PF_SERCOM_ALT,		/*peripheral functions D alternative UART.*/
	GPIO_Driver_PF_TIMER,			/*peripheral functions E Timer.*/
	GPIO_Driver_PF_TIMER_ALT,		/*peripheral functions F alternative Timer.*/
	GPIO_Driver_PF_TIMER_COM,		/*peripheral functions G I2S,JTAG/SWD pins.*/
	GPIO_Driver_PF_TIMER_GCLK_IO	/*peripheral functions H GCLK_IO (Generic Clock).*/
}GPIO_Driver_PinConfig;

typedef struct
{
	const GPIO_Driver_Instances GPIO_Port;
	const uint16 GPIO_Pin_nr;
	const uint8* GPIO_Pins;
	const GPIO_Driver_PinModes* GPIO_Pin_Mode;
	const GPIO_Driver_Input_Config* GPIO_Input_Config;
	const GPIO_Driver_Output_Config* GPIO_Output_Config;
	const GPIO_Driver_PinPullUp* GPIO_Pin_Pullup;
	const GPIO_Driver_PinConfig* GPIO_Pin_Cfg;
}GPIO_Driver_Setup_Type;

extern GPIO_Driver_Setup_Type* GPIO_SETUP;

/*---------------------------------------Generic GPIO APIs---------------------------------------*/
void 	GPIO_Driver_Init();
void 	GPIO_Driver_SetPin( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );
void 	GPIO_Driver_ClearPin( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );
uint32	GPIO_Driver_ReadInputData( GPIO_Driver_Instances GPIO_setup_nr );
uint32	GPIO_Driver_ReadOutputData( GPIO_Driver_Instances GPIO_setup_nr );
uint8	GPIO_Driver_ReadInputDataBit( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );
void	GPIO_Driver_Lambda_function();
void 	GPIO_Driver_Peripheral_Config( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );
void 	GPIO_Driver_PORT_Peripheral_Config( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );
void 	GPIO_Driver_PMUX_Peripheral_Config( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );
/*---------------------------------------MCU Specific GPIO APIs---------------------------------------*/
void 	GPIO_Driver_TogglePin( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin );

#endif /* GPIO_DRIVER_H_ */