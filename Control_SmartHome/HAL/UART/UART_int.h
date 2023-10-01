/*
 * UART_int.h
 *
 *  Created on: Sep 22, 2023
 *      Author: Emii
 */

#ifndef MCAL_UART_V1_UART_INT_H_
#define MCAL_UART_V1_UART_INT_H_
#include"LIB_STD_TYPES.h"

//***************************************************************************************//

void UART_voidInit (void);
/*Synchronous*/
void UART_voidSynchSendChar (uint8 Copy_u8data);
void UART_voidSynchSendString(uint8 *Copy_u8String);
uint8 UART_u8SynchRecieveChar(void);

/*Asynchronous*/
void UART_voidAynchSendChar (uint8 Copy_u8data);
void UART_voidAsynchSendString(uint8 *Copy_u8String);
uint8 UART_u8AsynchRecieveChar(void);
uint8* UART_u8AsynchRecieveString(void);

/*Call Back*/
//Receive Complete
void UART_voidCallBackRxComplete(void(*ptr)(void));
//Data Register Empty
void UART_voidCallBackDataRegEmpty(void(*ptr)(void));
//Transmission Complete
void UART_voidCallBackTxComplete(void(*ptr)(void));

/*                ISR
 * Vector
 *   No
 *   14 $01A USART, RXC USART, Rx Complete
 *   15 $01C USART, UDRE USART Data Register Empty
 *   16 $01E USART, TXC USART, Tx Complete
*/
void __vector_13(void) __attribute__((signal));
void __vector_14(void) __attribute__((signal));
void __vector_15(void) __attribute__((signal));

#endif /* MCAL_UART_V1_UART_INT_H_ */
