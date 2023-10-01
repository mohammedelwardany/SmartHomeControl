/*
 * UART_prog.c
 *
 *  Created on: Sep 22, 2023
 *      Author: Emii
 */

#include "LIB_STD_TYPES.h"
#include "LIB_BIT_MATH.h"
#include "UART_cfg.h"
#include "UART_int.h"
#include "UART_prv.h"

//Global Array and char to be filled by the ISR
uint8 Global_u8UARTRecieveArray[100] = {'\0'};
uint8 Global_u8UARTRecieveChar = '\0';
uint8 SendStringFlag = 0;
uint8* Global_String = NULL;

//Global Function to be passed to the ISR
void (*pfuncUART_RxComplete_ISR)(void);
void (*pfuncUART_DataEmpty_ISR)(void);
void (*pfuncUART_TxComplete_ISR)(void);

//***************************************INITIALIZATION**********************************************//

void UART_voidInit (void)
{
	/* Baud Rate*/
#if   MODE_SPEED == ASYNCHROUNUS_NORMAL_SPEED
	CLR_BIT(UCSRC,UCSRC_UMSEL); //Asynch mode
	UBRRL = (uint8)( ((uint32)F_OSC / (uint32)((uint32)16 * (uint32)BAUD_RATE)) - (uint32)1);
#elif MODE_SPEED == ASYNCHROUNUS_DOUBLE_SPEED
	//IN UCSRA Bit 1 – U2X: Double the USART Transmission Speed
	CLR_BIT(UCSRC,UCSRC_UMSEL); //Asynch mode
	//ENABLE U2X
	SET_BIT(UCSRA,UCSRA_U2X);
	UBRRL = (uint8)( ((uint32)F_OSC / (uint32)((uint32)8 * (uint32)BAUD_RATE)) - (uint32)1);

#elif MODE_SPEED == SYNCHROUNUS_MASTER_MODE
	SET_BIT(UCSRC,UCSRC_UMSEL); //Synch Mode
	UBRRL = (uint8)( ((uint32)F_OSC / (uint32)((uint32)2 * (uint32)BAUD_RATE)) - (uint32)1);
	//The UCPOL bit sets the relationship between data output change and data input sample, and the synchronous clock (XCK).
#if CLOCK_POLARITY == TX_CHANGED_ON_RISING_RX_SAMPLED_ON_FALLING
	CLR_BIT(UCSRC,UCSRC_UCPOL);
#elif CLOCK_POLARITY == TX_CHANGED_ON_FALLING_RX_SAMPLED_ON_RISING
	SET_BIT(UCSRC,UCSRC_UCPOL);
#endif
#endif

	/*Frame Format*/
	//Data (5 -> 9)
#if DATA_SIZE == 5
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	//WORK WITH 8-DATA BITS + ACCESS UCSRC REG.
	UCSRC |= ((1<<UCSRC_URSEL)|(0<<UCSRC_UCSZ1)|(0<<UCSRC_UCSZ0)) ;
#elif DATA_SIZE == 6
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	//WORK WITH 8-DATA BITS + ACCESS UCSRC REG.
	UCSRC |= ((1<<UCSRC_URSEL)|(0<<UCSRC_UCSZ1)|(1<<UCSRC_UCSZ0)) ;
#elif DATA_SIZE == 7
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	//WORK WITH 8-DATA BITS + ACCESS UCSRC REG.
	UCSRC |= ((1<<UCSRC_URSEL)|(1<<UCSRC_UCSZ1)|(0<<UCSRC_UCSZ0)) ;
#elif DATA_SIZE == 8
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	//WORK WITH 8-DATA BITS + ACCESS UCSRC REG.
	UCSRC |= ((1<<UCSRC_URSEL)|(1<<UCSRC_UCSZ1)|(1<<UCSRC_UCSZ0)) ;
#elif DATA_SIZE == 9
	SET_BIT(UCSRB,UCSRB_UCSZ2);
	//WORK WITH 8-DATA BITS + ACCESS UCSRC REG.
	UCSRC |= ((1<<UCSRC_URSEL)|(1<<UCSRC_UCSZ1)|(1<<UCSRC_UCSZ0)) ;
#endif

	//Stop (1 , 2)
#if STOP_BITS == 1
	CLR_BIT(UCSRC,UCSRC_USBS);
#elif STOP_BITS == 2
	SET_BIT(UCSRC,UCSRC_USBS);
#endif

	//Parity (Even - ODD -No Parity)
#if PARITY == NO_PARITY
	UCSRC |= ((0<<UCSRC_UPM1)|(0<<UCSRC_UPM0)) ;
#elif PARITY == EVEN_PARITY
	UCSRC |= ((1<<UCSRC_UPM1)|(0<<UCSRC_UPM0)) ;
#elif PARITY == ODD_PARITY
	UCSRC |= ((1<<UCSRC_UPM1)|(1<<UCSRC_UPM0)) ;
#endif

	/*Transmission*/ //Transmitter - Reciever - Tranceiver
#if TRANSMISIION_MODE == TRANSMITTER
	//ENABLE TX
	UCSRB |= ((1<<UCSRB_TXEN));
#elif TRANSMISIION_MODE == RECIEVER
	//ENABLE RX
	UCSRB |= (1<<UCSRB_RXEN) ;
#elif TRANSMISIION_MODE == TRANSIVER
	//ENABLE TX AND RX
	UCSRB |= ((1<<UCSRB_TXEN)|(1<<UCSRB_RXEN)) ;
#endif
}

//*************************************SYNCHRONOUS FUNCTIONS*************************************//
//********************************************POLLING*******************************************//

void UART_voidSynchSendChar (uint8 Copy_u8data)
{
	UDR = Copy_u8data;
	/*polling while reg is empty and ready to Recieve Bit 5 – UDRE: USART Data Register Empty*/
	while (GET_BIT(UCSRA,UCSRA_UDRE)==0);
}

void UART_voidSynchSendString(uint8 *Copy_u8String)
{
	uint8 i = 0 ;
	while ( Copy_u8String[i] != '\0')
	{
		UART_voidSynchSendChar( Copy_u8String [i]);
		i++;
	}
}

uint8 UART_u8SynchRecieveChar(void)
{
	/*polling while Recieve Complete Bit 7 – RXC: USART Receive Complete*/
	while (GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}

//**************************************ASYNCHRONOUS FUNCTIONS*************************************//
//********************************************Interrupt*******************************************//

void UART_voidAynchSendChar (uint8 Copy_u8data)
{
	//Enable the interrupt
	SET_BIT(UCSRB,UCSRB_RXCIE);
	UDR = Copy_u8data;
}

void UART_voidAsynchSendString(uint8 *Copy_u8String)
{
	SendStringFlag = 1;
	Global_String = Copy_u8String;
	UART_voidAynchSendChar(Copy_u8String[0]);
}

uint8 UART_u8AsynchRecieveChar(void)
{
	//Enable the interrupt
	SET_BIT(UCSRB,UCSRB_RXCIE);
	return Global_u8UARTRecieveChar;
}

uint8* UART_u8AsynchRecieveString(void)
{
	//Enable the interrupt
	SET_BIT(UCSRB,UCSRB_RXCIE);
	return Global_u8UARTRecieveArray;
}

//***************************************CALL BACK FUNCTIONS***************************************//

/*Call Back*/
//Receive Complete
void UART_voidCallBackRxComplete(void(*ptr)(void))
{
	pfuncUART_RxComplete_ISR = ptr;
}

//Data Register Empty
void UART_voidCallBackDataRegEmpty(void(*ptr)(void))
{
	pfuncUART_DataEmpty_ISR = ptr;
}

//Transmission Complete
void UART_voidCallBackTxComplete(void(*ptr)(void))
{
	pfuncUART_TxComplete_ISR = ptr;
}

//********************************************ISR************************************************//

void __vector_13(void)
{
	static uint8 i;
	Global_u8UARTRecieveChar = UDR;
	Global_u8UARTRecieveArray[i] = Global_u8UARTRecieveChar;
	i++;
	pfuncUART_RxComplete_ISR();
}

void __vector_14(void)
{
	pfuncUART_DataEmpty_ISR();
}

void __vector_15(void)
{
	static uint8 i = 1;
	if(SendStringFlag == 1)
	{
		UART_voidAynchSendChar(Global_String[i]);
		i++;
		if(Global_String[i] == '\0')
		{
			UART_voidAynchSendChar(Global_String[i]);
			SendStringFlag = 0;
		}
	}
	pfuncUART_TxComplete_ISR();
}
