/*
 * StdTypes.h
 *
 * Created: 05/20/2024 12:50:44 PM
 *  Author: EBALOZS4C
 */ 


#ifndef STDTYPES_H_
#define STDTYPES_H_

#include "stdint.h"

/*Generic*/
#define TRUE 				0x01
#define FALSE 				0x00
#define _DEFAULT_           0x00
#define OK 					0x01
#define NOK 				0x00
#define ON 					0x01
#define OFF 				0x00
#define _SUCCESS_			((uint8)0x00)
#define _FAILED_			((uint8)0x01)
#define _NULL_PTR			((void *)0x00)
#define uint8				uint8_t
#define uint16				uint16_t
#define uint32				uint32_t
#define uint64				uint64_t
#define int32               int32_t
#define MAX8				0xFF
#define MAX16				0xFFFF
#define MAX32				0xFFFFFFFF
#define MIN8				0x00
#define MIN16				0x0000
#define MIN32				0x00000000
#define _UNUSED_(PARAM)     ((void)(PARAM))

#endif /* STDTYPES_H_ */