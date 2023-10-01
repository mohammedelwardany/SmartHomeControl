/*
 * I2C_int.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

#ifndef MCAL_I2C_V1_I2C_INT_H_
#define MCAL_I2C_V1_I2C_INT_H_

/* UTILES_LIB */
#include "LIB_STD_TYPES.h"

void TWI_voidInitMaster           (uint8 Copy_u8Add);
void TWI_voidSendStartCondition   (void);
void TWI_voidSendRepStartCondition(void);
void TWI_voidSendStopCondition    (void);
void TWI_voidSendSlaveAddWithWrite(uint8 Copy_u8SlaveAdd);
void TWI_voidSendSlaveAddWithRead (uint8 Copy_u8SlaveAdd);
void TWI_voidSendMasterDataByte   (uint8 Copy_u8TxData);
void TWI_voidRecieveMasterDataByte(uint8* Copy_pu8RxData);

#endif /* MCAL_I2C_V1_I2C_INT_H_ */
