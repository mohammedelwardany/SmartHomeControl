/*
 * SPI_int.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

#ifndef MCAL_SPI_V1_SPI_INT_H_
#define MCAL_SPI_V1_SPI_INT_H_
#include "LIB_STD_TYPES.h"

void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);
uint8 SPI_u8Tranceiver(uint8 Copy_u8data);

/*******************************************ISR*********************************************/
/*Call Back*/
//Transfer Complete
void SPI_voidCallBackSTCcomplete(void(*ptr)(void));

/* Vector
 *  Num
 *  13      SPI, STC Serial Transfer Complete*/
void __vector_12(void) __attribute__((signal));

#endif /* MCAL_SPI_V1_SPI_INT_H_ */
