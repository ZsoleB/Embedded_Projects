/*
 * USART_Driver.h
 *
 *  Created on: 9 apr. 2018
 *      Author: Zsole
 */

#ifndef DRIVERS_USART_DRIVER_USART_DRIVER_H_
#define DRIVERS_USART_DRIVER_USART_DRIVER_H_

#include "RegMemmap.h"

#define USART_DRIVER_ASYNCH_COMM          	((uint32)(0x00<<0x1C))		/*This bit selects asynchronous communication.*/
#define USART_DRIVER_SYNCH_COMM				((uint32)(0x01<<0x1C))		/*This bit selects synchronous communication.*/
#define USART_DRIVER_FRAME_FORM_NOPAR		((uint32)(0x00<<0x18))		/*These bits define the frame format with no parity*/
#define USART_DRIVER_FRAME_FORM_PARITY		((uint32)(0x01<<0x18))		/*These bits define the frame format with parity*/
#define USART_DRIVER_ONE_STOP_BIT         	((uint32)(0x00<<0x06))		/*Stop bit mode, with one stop bit selection*/
#define USART_DRIVER_TWO_STOP_BITS        	((uint32)(0x01<<0x06))		/*Stop bit mode, with two stop bits selection*/
#define USART_DRIVER_EVEN_PARITY          	((uint32)(0x00<<0x0D))		/*Parity mode, with even parity selection*/
#define USART_DRIVER_ODD_PARITY           	((uint32)(0x01<<0x0D))		/*Parity mode, with odd parity selection*/
#define USART_DRIVER_RXEN                 	((uint32)(0x01<<0x11))		/*Receiver enable*/
#define USART_DRIVER_TXEN                 	((uint32)(0x01<<0x10))		/*Transmitter enable*/
#define USART_DRIVER_IBON                 	((uint32)(0x00<<0x02))		/*Immediate Buffer Overflow Notification - controls when the buffer overflow status bit (STATUS.BUFOVF) is asserted when a buffer overflow occurs.*/
#define USART_DRIVER_EXT_CLOCK            	((uint32)(0x00<<0x02))		/*Select the external clock*/
#define USART_DRIVER_INT_CLOCK            	((uint32)(0x01<<0x02))		/*Select the internal clock*/
#define USART_DRIVER_ENABLE               	((uint32)(0x01<<0x01))		/*Enable the USART module*/
#define USART_DRIVER_SWRESET              	((uint32)0x01UL)			/*Writing '1' to this bit resets all registers in the SERCOM, except DBGCTRL, to their initial state, and the SERCOM will be disabled.*/
		
typedef enum
{
	USART_DRIVER_FLAG_STATUS_ERROR	= 0x80,				/*This bit is set when any error is detected (COLL, ISF, BUFOVF, FERR, PERR)*/
	USART_DRIVER_FLAG_STATUS_RXBRK 	= 0x20,				/*This flag is set when auto-baud is enabled (CTRLA.FORM) and a break character is received.*/
	USART_DRIVER_FLAG_STATUS_CTSIC  = 0x10,				/*This flag is set when a change is detected on the CTS pin.*/
	USART_DRIVER_FLAG_STATUS_RXS  	= 0x08,				/*This flag is set when a start condition is detected on the RxD line and start-of-frame detection is enabled (CTRLB.SFDE is '1').*/
	USART_DRIVER_FLAG_STATUS_RXC 	= 0x04,				/*This flag is set when there are unread data in DATA.*/
	USART_DRIVER_FLAG_STATUS_TXC 	= 0x02,				/*This flag is set when the entire frame in the transmit shift register has been shifted out and there are no new data in DATA.*/
	USART_DRIVER_FLAG_STATUS_DRE 	= 0x01				/*This flag is set when DATA is empty and ready to be written.*/
}USART_Driver_ComStatus_bits;

typedef enum
{
	USART_DRIVER_TXE_STATUS  	= 0x40,				/*Transmitter Empty*/
	USART_DRIVER_COLL_STATUS 	= 0x20,				/*Collision Detected*/
	USART_DRIVER_ISF_STATUS  	= 0x10,				/*Inconsistent Sync Field*/
	USART_DRIVER_CTS_STATUS  	= 0x08,				/*Clear to Send*/
	USART_DRIVER_BUFOVF_STATUS 	= 0x04,				/*Buffer Overflow*/
	USART_DRIVER_FERR_STATUS 	= 0x02,				/*Frame Error*/
	USART_DRIVER_PERR_STATUS 	= 0x01				/*Parity Error*/
}USART_Driver_ErrStatus_bits;

typedef enum
{
	USART_DRIVER_SYNCH_SWRST  = 0x01,				/*Software Reset Synchronization Busy*/
	USART_DRIVER_SYNCH_ENABLE = 0x02,				/*SERCOM Enable Synchronization Busy*/
	USART_DRIVER_SYNCH_CTRLB  = 0x04,				/*CTRLB Synchronization Busy*/
}USART_Driver_Synchronization_bits;

typedef enum
{
	USART_DRIVER_8_bits = 0x00,						  /*8 bit sized character.*/
	USART_DRIVER_9_bits = 0x01,						  /*9 bit sized character.*/
	USART_DRIVER_5_bits = 0x05,						  /*5 bit sized character.*/
	USART_DRIVER_6_bits = 0x06,						  /*6 bit sized character.*/
	USART_DRIVER_7_bits = 0x07						  /*7 bit sized character.*/
}USART_Driver_Characther_Size;

typedef enum
{
	USART_DRIVER_PARITY_NONE,						  /*Parity will not be used*/
	USART_DRIVER_PARITY_USE						      /*Parity will be used*/
}USART_Driver_ParityEnable_Config;

typedef enum
{
	USART_DRIVER_PARITY_DEFAULT=0,				  	/*Parity mode selection can be ignored*/
	USART_DRIVER_PARITY_EVEN=0,						/*Parity mode selection set to even*/
	USART_DRIVER_PARITY_ODD=1						/*Parity mode selection set to odd*/
}USART_Driver_Parity_Config;

typedef enum
{
	USART_DRIVER_RECEIVE_DISABLE,					/*Disable the reception option*/
	USART_DRIVER_RECEIVE_ENABLE						/*Enable the reception option*/
}USART_Driver_Receive_Config;

typedef enum
{
	USART_DRIVER_TRANSMIT_DISABLE,					/*Disable the transmission option*/
	USART_DRIVER_TRANSMIT_ENABLE					/*Enable the transmission option*/
}USART_Driver_Transmit_Config;

typedef enum
{
	USART_DRIVER_STOPBIT_ONE,						/*Set Stop bit mode to one*/
	USART_DRIVER_STOPBIT_TWO						/*Set Stop bit mode to two*/
}USART_Driver_StopBitMode_Config;

typedef enum
{
	USART_DRIVER_RX_PINOUT_DEFAULT 	= 0x00,			/*The reception is not used so the pin out is to be ignored*/
	USART_DRIVER_RX_PINOUT_PAD0		= 0x00,			/*Use the pin mapped to PAD0*/
	USART_DRIVER_RX_PINOUT_PAD1 	= 0x01,			/*Use the pin mapped to PAD1*/
	USART_DRIVER_RX_PINOUT_PAD2 	= 0x02,			/*Use the pin mapped to PAD2*/
	USART_DRIVER_RX_PINOUT_PAD3 	= 0x03,			/*Use the pin mapped to PAD3*/
}USART_Driver_RX_PinOut_Config;

typedef enum
{
	USART_DRIVER_TX_PINOUT_DEFAULT	= 0x00,			/*The transmission is not used so the pin out is to be ignored*/
	USART_DRIVER_TX_PINOUT_PAD0 	= 0x00,			/*Use the pin mapped to PAD0*/
	USART_DRIVER_TX_PINOUT_PAD2		= 0x01			/*Use the pin mapped to PAD2*/
}USART_Driver_TX_PinOut_Config;

typedef enum
{
	USART_DRIVER_16X_OVER_SAMPLING_ARITH = 0x00,		/*16x over-sampling using arithmetic baud rate generation.*/
	USART_DRIVER_16X_OVER_SAMPLING_FRACT = 0x01,		/*16x over-sampling using fractional baud rate generation.*/
	USART_DRIVER_8X_OVER_SAMPLING_ARITH  = 0x02,		/*8x over-sampling using arithmetic baud rate generation.*/
	USART_DRIVER_8X_OVER_SAMPLING_FRACT  = 0x03,		/*8x over-sampling using fractional baud rate generation.*/
}USART_Driver_SampleRate_Config;

typedef enum
{
	USART_DRIVER_MSB_FIRST,			/*Select the USART instance from the SERCOM 0*/
	USART_DRIVER_LSB_FIRST,			/*Select the USART instance from the SERCOM 1*/
}USART_Driver_Data_Order;

typedef enum
{
	USART_DRIVER_0,									/*Select the USART instance from the SERCOM 0*/
	USART_DRIVER_1,									/*Select the USART instance from the SERCOM 1*/
	USART_DRIVER_2,									/*Select the USART instance from the SERCOM 2*/
	USART_DRIVER_3,									/*Select the USART instance from the SERCOM 3*/
	USART_DRIVER_4,									/*Select the USART instance from the SERCOM 4*/
	USART_DRIVER_5									/*Select the USART instance from the SERCOM 5*/
}USART_Driver_Instances;

typedef struct
{
	const USART_Driver_Instances USART_Instance;
	const uint16 USART_Baudrate;
	const USART_Driver_Characther_Size USART_Word_length;
	const USART_Driver_ParityEnable_Config USART_Parity_control_enable;
	const USART_Driver_Parity_Config USART_Parity_selection;
	const USART_Driver_Transmit_Config USART_Transmitter_enable;
	const USART_Driver_TX_PinOut_Config	USART_Driver_TX_PinOut;
	const USART_Driver_Receive_Config USART_Receiver_enable;
	const USART_Driver_RX_PinOut_Config	USART_Driver_RX_PinOut;
	const USART_Driver_StopBitMode_Config USART_Stop_bit_select;
	const USART_Driver_SampleRate_Config USART_Oversampling_mode;
	const USART_Driver_Data_Order USART_Payload_Data_Order;
}USART_Driver_Setup_Type;

extern USART_Driver_Setup_Type* USART_SETUP;
extern SERCOM_DRIVER_Register_Group* SERCOM_DRIVER_Registers[6];

void USART_Driver_Init();
void USART_Driver_Set_Baudrate(USART_Driver_Instances USART_setup_nr);
uint8 USART_Driver_Receive_Char(USART_Driver_Instances USART_setup_nr);
void USART_Driver_Send_Char(USART_Driver_Instances USART_setup_nr,uint8 data);
void USART_Driver_Send_Str(USART_Driver_Instances USART_setup_nr,char* Msg);
void USART_Driver_Start(USART_Driver_Instances USART_setup_nr);
void USART_Driver_Stop(USART_Driver_Instances USART_setup_nr);
uint8 USART_Driver_GetComStatus(USART_Driver_Instances USART_setup_nr, USART_Driver_ComStatus_bits Status_Bit);
uint8 USART_Driver_GetErrStatus(USART_Driver_Instances USART_setup_nr, USART_Driver_ErrStatus_bits Status_Bit);
void USART_Driver_SWReset(USART_Driver_Instances USART_setup_nr);

#endif /* DRIVERS_USART_DRIVER_USART_DRIVER_H_ */
