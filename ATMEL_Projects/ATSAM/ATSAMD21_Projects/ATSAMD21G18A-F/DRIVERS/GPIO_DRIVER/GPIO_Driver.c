/*
 * GPIO_Driver.c
 *
 * Created: 05/20/2024 12:57:52 PM
 *  Author: EBALOZS4C
 */ 
#include "GPIO_Driver_Cfg.h"

/*---------------------------------------Generic GPIO APIs---------------------------------------*/

/*Initialize the selected GPIO modules*/
void GPIO_Driver_Init()
{
	uint8 Port_index = 0x00;
	uint32 Pin_index = 0x00;
		
	/*Enable the PORT clock on APB bus*/
	/*To do: after system files added, change magic number to bit position*/
	SYSTEM_PM_DRIVER_REG->SYSTEM_PM_APBBMASK |= (1<<3);

	for(Port_index=0x00;Port_index<GPIO_DRIVER_INSTANCE_NUM;Port_index++)
	{
		/*Extract the PORT Associated with the GPIO Driver instance.*/
		GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[Port_index].GPIO_Port;
    
		/*Set the registers bellow to their reset values:
		 	GPIO direction, 
			Output, 
			Control, 
			Write configuration,
		*/
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_DIR = (uint32)0x00;
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUT = (uint32)0x00;
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_CTRL = (uint32)0x00;
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_WRCONFIG = (uint32)0x00;

		for(Pin_index=0x00;Pin_index<GPIO_SETUP[Port_index].GPIO_Pin_nr;Pin_index++)
		{
			GPIO_Driver_Peripheral_Config(GPIO_SETUP[eSelected_Port].GPIO_Port,Pin_index);
		}
	}
}

/*Set the selected pin to 1*/
void GPIO_Driver_SetPin( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin )
{
	/*Extract the PORT Associated with the GPIO Driver instance.*/
	GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[GPIO_setup_nr].GPIO_Port;

	/*Set the PIN of the previously selected port to 1.*/
	GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUTSET |= (uint32)(1<<Pin);
}

/*Clear the selected pin*/
void GPIO_Driver_ClearPin( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin )
{
	/*Extract the PORT Associated with the GPIO Driver instance.*/
	GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[GPIO_setup_nr].GPIO_Port;

	/*Clear the PIN of the previously selected port.*/
	GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUTCLR |= (uint32)(1<<Pin);
}

/*Read the value of the input data (the value of all the bits)*/
uint32 GPIO_Driver_ReadInputData( GPIO_Driver_Instances GPIO_setup_nr )
{
	uint32 result = 0x00;

	/*Extract the PORT Associated with the GPIO Driver instance.*/
	GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[GPIO_setup_nr].GPIO_Port;	
	
	/*Read the PINS of the previously selected port.*/
	result = (uint32)(GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_IN);
	
	return result;
}

/*Read the value of the input data (the value of only one bit)*/
uint8 GPIO_Driver_ReadInputDataBit( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin )
{
	uint32 input = 0x00;
	uint8 result = 0x00;
	
	/*Extract the PORT Associated with the GPIO Driver instance.*/
	GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[GPIO_setup_nr].GPIO_Port;	

	/*Read the PIN of the previously selected port.*/
	input = (uint32)(GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_IN);	
	
	/*Check if the requested index is set.*/
	result = ((input & ((uint32)(0x01<<Pin))) != 0x00) ? 1 : 0;

	return result;
}

/*Read the value of the output data register(the value of all the bits)*/
uint32 GPIO_Driver_ReadOutputData( GPIO_Driver_Instances GPIO_setup_nr )
{
	uint32 result = 0x00;

	/*Extract the PORT Associated with the GPIO Driver instance.*/
	GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[GPIO_setup_nr].GPIO_Port;	
	
	/*Read the output PINS of the previously selected port.*/
	result = (uint32)(GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUT);

	return result;
}

void GPIO_Driver_Peripheral_Config( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin )
{
	switch(GPIO_SETUP[GPIO_setup_nr].GPIO_Pin_Cfg[Pin])
	{
		case GPIO_Driver_PF_GPIO:
			GPIO_Driver_PORT_Peripheral_Config(GPIO_setup_nr,Pin);
			break;
		case GPIO_Driver_PF_EXTINT:
		case GPIO_Driver_PF_ANALOG:
		case GPIO_Driver_PF_SERCOM:
		case GPIO_Driver_PF_SERCOM_ALT:
		case GPIO_Driver_PF_TIMER:
		case GPIO_Driver_PF_TIMER_ALT:
		case GPIO_Driver_PF_TIMER_COM:
		case GPIO_Driver_PF_TIMER_GCLK_IO:
			GPIO_Driver_PMUX_Peripheral_Config(GPIO_setup_nr,Pin);
			break;
		default:
			break;
	};
}

/*Configure the Port related Pins.*/
void GPIO_Driver_PORT_Peripheral_Config( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin )
{
	/*Extract the PORT Associated with the GPIO Driver instance.*/
	GPIO_Driver_Instances eSelected_Port = GPIO_SETUP[GPIO_setup_nr].GPIO_Port;	
  uint8 uSelected_Pin = GPIO_SETUP[GPIO_setup_nr].GPIO_Pins[Pin];	

	/*Clear out the previous config*/
	GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_DIR &= (uint32)(~(0x01 << uSelected_Pin));
	GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUT &= (uint32)(~(0x01 << uSelected_Pin));
	GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_PINCFG[uSelected_Pin] = (uint8)0x00;

	/*
		The input samplers are enabled and disabled in sub-groups of eight. 
		Thus if any pins within a byte request continuous sampling, all pins 
		in  that eight pin sub-group will be continuously sampled.
	*/
		
	GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_CTRL &= (uint32)(~(0x01 << uSelected_Pin));

	/*Configure the Pins to INPUT or to OUTPUT according to the configuration buffer.*/
	if(GPIO_Driver_PinMode_INPUT == GPIO_SETUP[GPIO_setup_nr].GPIO_Pin_Mode[Pin])
	{	
		/*Set the PORT direction to INPUT*/	
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_DIRCLR |= (uint32)(1 << uSelected_Pin);
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_PINCFG[uSelected_Pin] |= (uint8)(GPIO_DRIVER_INPUT_EN << uSelected_Pin);
		/*Set the configured sampling mode.*/
		if(GPIO_Driver_Input_Sampling_ON_DEMAND == GPIO_SETUP[GPIO_setup_nr].GPIO_Input_Config[Pin])
		{
			GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_CTRL |= (uint32)(GPIO_DRIVER_ON_DEMAND_SAMPLING << uSelected_Pin); 
		}
		else if(GPIO_Driver_Input_Sampling_CONTINUOUS == GPIO_SETUP[GPIO_setup_nr].GPIO_Input_Config[Pin])
		{
			GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_CTRL |= (uint32)(GPIO_DRIVER_CONTINOUS_SAMPLING << uSelected_Pin);
		}
		else
		{
			/*Nothing to do here*/
		}

		/*Set Pull resistor according to the configuration buffer*/
		switch(GPIO_SETUP[GPIO_setup_nr].GPIO_Pin_Pullup[Pin])
		{
			/*Set Pull-Up resistor*/
			case GPIO_Driver_PinMode_PULLUP:
			
				GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_PINCFG[uSelected_Pin] |= (uint8)(GPIO_DRIVER_PULL_EN << uSelected_Pin);
				GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUTSET |= (uint32)(0x01<<uSelected_Pin);
				break;
			/*Set Pull-Down resistor*/
			case GPIO_Driver_PinMode_PULLDOWN:
			
				GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_PINCFG[uSelected_Pin] |= (uint8)(GPIO_DRIVER_PULL_EN << uSelected_Pin);
				GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_OUTCLR |= (uint32)(0x01<<uSelected_Pin);
				break;
			/*No pull-up will be set*/
			case GPIO_Driver_PinMode_NO_PULL:
			default:
				break;
		};
	}
	else if(GPIO_Driver_PinMode_OUTPUT == GPIO_SETUP[GPIO_setup_nr].GPIO_Pin_Mode[Pin])
	{
		/*Set the PORT direction to OUTPUT*/	
		GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_DIRSET |= (uint32)(GPIO_DRIVER_OUTPUT_MODE << uSelected_Pin);

		if(GPIO_Driver_Output_Normal_Drive_Strength == GPIO_SETUP[GPIO_setup_nr].GPIO_Output_Config[Pin])
		{
			GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_PINCFG[uSelected_Pin] |= (uint8)(GPIO_DRIVER_DRVSTR_NORMAL << uSelected_Pin);
		}
		else if(GPIO_Driver_Output_Strong_Drive_Strength == GPIO_SETUP[GPIO_setup_nr].GPIO_Output_Config[Pin])
		{
			GPIO_DRIVER_PORT_REG->PORT_Group[eSelected_Port].GPIO_DRIVER_PINCFG[uSelected_Pin] |= (uint8)(GPIO_DRIVER_DRVSTR_STRONG << uSelected_Pin);
		}
		else
		{
			/*Nothing to do here*/
		}
	}
	else
	{
		/*Nothing to do*/
	}
}

void GPIO_Driver_PMUX_Peripheral_Config( GPIO_Driver_Instances GPIO_setup_nr, uint8 Pin )
{
	/*To do: implement alternate function implementation*/
}

/*To Do:
	Implement group configuration for PORTx
*/