///*
// * RFID_Module.c
// *
// *  Created on: Sep 19, 2018
// *      Author: zsolt.balo
// */
//
//#include "RFID_Module.h"
//
//void TM_MFRC522_Init(void) {
//
//	TM_MFRC522_Reset();
//
//	TM_MFRC522_WriteRegister(MFRC522_REG_T_MODE, 0x8D);
//	TM_MFRC522_WriteRegister(MFRC522_REG_T_PRESCALER, 0x3E);
//	TM_MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_L, 30);
//	TM_MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_H, 0);
//
//	/* 48dB gain */
//	TM_MFRC522_WriteRegister(MFRC522_REG_RF_CFG, 0x70);
//
//	TM_MFRC522_WriteRegister(MFRC522_REG_TX_AUTO, 0x40);
//	TM_MFRC522_WriteRegister(MFRC522_REG_MODE, 0x3D);
//
//	TM_MFRC522_AntennaOn();		//Open the antenna
//}
//
//TM_MFRC522_Status_t RFID_Module_MFRC522_Check(uint8_t* id) {
//	TM_MFRC522_Status_t status;
//	//Find cards, return card type
//	status = TM_MFRC522_Request(PICC_REQIDL, id);
//	if (status == MI_OK) {
//		//Card detected
//		//Anti-collision, return card serial number 4 bytes
//		status = TM_MFRC522_Anticoll(id);
//	}
//	TM_MFRC522_Halt();			//Command card into hibernation
//
//	return status;
//}
//
//TM_MFRC522_Status_t RFID_Module_MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID) {
//	uint8_t i;
//	for (i = 0; i < 5; i++) {
//		if (CardID[i] != CompareID[i]) {
//			return MI_ERR;
//		}
//	}
//	return MI_OK;
//}
//
//TM_MFRC522_Status_t TM_MFRC522_Request(uint8_t reqMode, uint8_t* TagType) {
//	TM_MFRC522_Status_t status;
//	uint16_t backBits;			//The received data bits
//
//	TM_MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x07);		//TxLastBists = BitFramingReg[2..0]	???
//
//	TagType[0] = reqMode;
//	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
//
//	if ((status != MI_OK) || (backBits != 0x10)) {
//		status = MI_ERR;
//	}
//
//	return status;
//}
//
//TM_MFRC522_Status_t TM_MFRC522_Anticoll(uint8_t* serNum) {
//	TM_MFRC522_Status_t status;
//	uint8_t i;
//	uint8_t serNumCheck = 0;
//	uint16_t unLen;
//
//	TM_MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x00);		//TxLastBists = BitFramingReg[2..0]
//
//	serNum[0] = PICC_ANTICOLL;
//	serNum[1] = 0x20;
//	status = TM_MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);
//
//	if (status == MI_OK) {
//		//Check card serial number
//		for (i = 0; i < 4; i++) {
//			serNumCheck ^= serNum[i];
//		}
//		if (serNumCheck != serNum[i]) {
//			status = MI_ERR;
//		}
//	}
//	return status;
//}
//
//void TM_MFRC522_Halt(void) {
//	uint16_t unLen;
//	uint8_t buff[4];
//
//	buff[0] = PICC_HALT;
//	buff[1] = 0;
//	TM_MFRC522_CalculateCRC(buff, 2, &buff[2]);
//
//	TM_MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
//}
//
//void TM_MFRC522_WriteRegister(uint8_t addr, uint8_t val) {
//
//	SPI_Driver_Set_Slave_Select_Low(SPI_DRIVER_0);
//	//Send address
//	SPI_Driver_Send_Data(SPI_DRIVER_0, (addr << 1) & 0x7E);
//	//Send data
//	SPI_Driver_Send_Data(SPI_DRIVER_0, val);
//
//	SPI_Driver_Set_Slave_Select_High(SPI_DRIVER_0);
//}
//
//uint8_t TM_MFRC522_ReadRegister(uint8_t addr) {
//
//	uint8_t val;
//
//	SPI_Driver_Set_Slave_Select_Low(SPI_DRIVER_0);
//
//	SPI_Driver_Send_Data(SPI_DRIVER_0, ((addr << 1) & 0x7E) | 0x80);
//	val = SPI_Driver_Send_Data(SPI_DRIVER_0, MFRC522_DUMMY);
//
//	SPI_Driver_Set_Slave_Select_High(SPI_DRIVER_0);
//
//	return val;
//}
//
//void TM_MFRC522_SetBitMask(uint8 reg, uint8 mask) {
//	TM_MFRC522_WriteRegister(reg, TM_MFRC522_ReadRegister(reg) | mask);
//}
//
//void TM_MFRC522_ClearBitMask(uint8 reg, uint8 mask){
//	TM_MFRC522_WriteRegister(reg, TM_MFRC522_ReadRegister(reg) & (~mask));
//}
//
//void TM_MFRC522_Reset(void) {
//	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_RESETPHASE);
//}
//
//void TM_MFRC522_AntennaOn(void) {
//	uint8_t temp;
//
//	temp = TM_MFRC522_ReadRegister(MFRC522_REG_TX_CONTROL);
//	if (!(temp & 0x03)) {
//		TM_MFRC522_SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
//	}
//}
//void TM_MFRC522_AntennaOff(void) {
//	TM_MFRC522_ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);
//}
//
//
//TM_MFRC522_Status_t TM_MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {
//	TM_MFRC522_Status_t status = MI_ERR;
//	uint8_t irqEn = 0x00;
//	uint8_t waitIRq = 0x00;
//	uint8_t lastBits;
//	uint8_t n;
//	uint16_t i;
//
//	switch (command) {
//		case PCD_AUTHENT: {
//			irqEn = 0x12;
//			waitIRq = 0x10;
//			break;
//		}
//		case PCD_TRANSCEIVE: {
//			irqEn = 0x77;
//			waitIRq = 0x30;
//			break;
//		}
//		default:
//			break;
//	}
//
//	TM_MFRC522_WriteRegister(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
//	TM_MFRC522_ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
//	TM_MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
//
//	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_IDLE);
//
//	//Writing data to the FIFO
//	for (i = 0; i < sendLen; i++) {
//		TM_MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, sendData[i]);
//	}
//
//	//Execute the command
//	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, command);
//	if (command == PCD_TRANSCEIVE) {
//		TM_MFRC522_SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);		//StartSend=1,transmission of data starts
//	}
//
//	//Waiting to receive data to complete
//	i = 2000;	//i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
//	do {
//		//CommIrqReg[7..0]
//		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
//		n = TM_MFRC522_ReadRegister(MFRC522_REG_COMM_IRQ);
//		i--;
//	} while ((i!=0) && !(n&0x01) && !(n&waitIRq));
//
//	TM_MFRC522_ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);			//StartSend=0
//
//	if (i != 0)  {
//		if (!(TM_MFRC522_ReadRegister(MFRC522_REG_ERROR) & 0x1B)) {
//			status = MI_OK;
//			if (n & irqEn & 0x01) {
//				status = MI_NOTAGERR;
//			}
//
//			if (command == PCD_TRANSCEIVE) {
//				n = TM_MFRC522_ReadRegister(MFRC522_REG_FIFO_LEVEL);
//				lastBits = TM_MFRC522_ReadRegister(MFRC522_REG_CONTROL) & 0x07;
//				if (lastBits) {
//					*backLen = (n - 1) * 8 + lastBits;
//				} else {
//					*backLen = n * 8;
//				}
//
//				if (n == 0) {
//					n = 1;
//				}
//				if (n > MFRC522_MAX_LEN) {
//					n = MFRC522_MAX_LEN;
//				}
//
//				//Reading the received data in FIFO
//				for (i = 0; i < n; i++) {
//					backData[i] = TM_MFRC522_ReadRegister(MFRC522_REG_FIFO_DATA);
//				}
//			}
//		} else {
//			status = MI_ERR;
//		}
//	}
//
//	return status;
//}
//
//void TM_MFRC522_CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {
//	uint8_t i, n;
//
//	TM_MFRC522_ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);			//CRCIrq = 0
//	TM_MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);			//Clear the FIFO pointer
//	//Write_MFRC522(CommandReg, PCD_IDLE);
//
//	//Writing data to the FIFO
//	for (i = 0; i < len; i++) {
//		TM_MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, *(pIndata+i));
//	}
//	TM_MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_CALCCRC);
//
//	//Wait CRC calculation is complete
//	i = 0xFF;
//	do {
//		n = TM_MFRC522_ReadRegister(MFRC522_REG_DIV_IRQ);
//		i--;
//	} while ((i!=0) && !(n&0x04));			//CRCIrq = 1
//
//	//Read CRC calculation result
//	pOutData[0] = TM_MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_L);
//	pOutData[1] = TM_MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_M);
//}
//
//TM_MFRC522_Status_t TM_MFRC522_Check(uint8_t* id) {
//	TM_MFRC522_Status_t status;
//	//Find cards, return card type
//	status = TM_MFRC522_Request(PICC_REQIDL, id);
//	if (status == MI_OK) {
//		//Card detected
//		//Anti-collision, return card serial number 4 bytes
//		status = TM_MFRC522_Anticoll(id);
//	}
//	TM_MFRC522_Halt();			//Command card into hibernation
//
//	return status;
//}
//
//TM_MFRC522_Status_t TM_MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID) {
//	uint8_t i;
//	for (i = 0; i < 5; i++) {
//		if (CardID[i] != CompareID[i]) {
//			return MI_ERR;
//		}
//	}
//	return MI_OK;
//}
