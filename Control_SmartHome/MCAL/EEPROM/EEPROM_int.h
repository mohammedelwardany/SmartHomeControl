/*
 * EEPROM_int.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

#ifndef HAL_EEPROM_EEPROM_INT_H_
#define HAL_EEPROM_EEPROM_INT_H_

void EEPROM_voidInit(void);
void EEPROM_voidWriteByte(uint16 Copy_u16WordAddress, uint8 Copy_u8Data);
void EEPROM_voidReadByte(uint16 Copy_u16WordAddress, uint8* Copy_pu8RxData);

void EEPROM_voidWritePage(uint16 Copy_u16WordAddress,uint8 Copy_u8size,uint8 *Copy_u8TransmitData);
void EEPROM_voidReadPage(uint16 Copy_u16WordAddress,uint8 Copy_u8size,uint8* Copy_u8pRecievedData);

#endif /* HAL_EEPROM_EEPROM_INT_H_ */
