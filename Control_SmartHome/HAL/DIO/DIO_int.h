/*
 *  DIO_int.h
 *
 *  Created on: Sep 8, 2023
 *      Author: Emii
 */

#ifndef MCAL_DIO_INT_H_
#define MCAL_DIO_INT_H_

#include "LIB_BIT_MATH.h"
#include "LIB_STD_TYPES.h"

typedef enum {
Pin_A0  ,Pin_A1	,Pin_A2	,Pin_A3	,Pin_A4	,Pin_A5	, Pin_A6 ,Pin_A7 ,
Pin_B0	,Pin_B1 ,Pin_B2 ,Pin_B3	,Pin_B4 ,Pin_B5	, Pin_B6 ,Pin_B7 ,
Pin_C0	,Pin_C1	,Pin_C2	,Pin_C3	,Pin_C4	,Pin_C5	, Pin_C6 ,Pin_C7 ,
Pin_D0	,Pin_D1	,Pin_D2	,Pin_D3	,Pin_D4	,Pin_D5	, Pin_D6 ,Pin_D7 ,
}Pin_Type;

typedef enum {
	OutPut_High , OutPut_Low,
	InPut_Float,InPut_PullUp
}PinMode_type;

typedef enum
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
}PORT_ID;

//***************************************************************************************//
//For 1 pin
typedef enum
{
	Low,
	High
}PIN_VAL;

//***************************************************************************************//
//For PORT
typedef enum
{
	Full_Low = 0x00,
	Full_High = 0xff
}PORT_VAL;

//***************************************************************************************//

//initializing for Direction and Value using Linking Time config
void DIO_voidInit(void);

//Pin by pin
void DIO_voidSetPinChMode(Pin_Type Copy_PinID, PinMode_type Copy_PinMode); //To change the mode in the runtime
void DIO_voidWritePinChannel(Pin_Type Copy_PinID, PIN_VAL Copy_Var);
void DIO_voidReadPinChannel(Pin_Type Copy_PinID, uint8* Copy_pBufferPtr);

//The Whole Port
void DIO_voidReadPortChannel(PORT_ID Copy_PortID, uint8* Copy_pBufferPtr);
void DIO_voidWritePortChannel(PORT_ID Copy_PortID, PORT_VAL Copy_Var);
void DIO_voidWritePortWithMask(PORT_ID Copy_PortID, uint8 Copy_Mask, uint8 Copy_Data);


#endif /* MCAL_DIO_V1_DIO_INT_H_ */
