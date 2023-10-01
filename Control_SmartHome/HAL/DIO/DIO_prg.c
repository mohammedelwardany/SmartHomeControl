/*
 * DIO_prg.c
 *
 *  Created on: Sep 8, 2023
 *      Author: Emii
 */
#include "DIO_cfg.h"
#include "DIO_int.h"
#include "DIO_prv.h"
#include "LIB_BIT_MATH.h"
#include "LIB_STD_TYPES.h"

uint8 * const DIO_RegPORT[4]={PORTA_Address,PORTB_Address,PORTC_Address,PORTD_Address};
uint8 * const DIO_RegDDR[4]= {DDRA_Address,DDRB_Address,DDRC_Address,DDRD_Address};
uint8 * const DIO_RegPIN[4]= {PINA_Address,PINB_Address,PINC_Address,PIND_Address};

//static u8 PortA,PortB,PortC,PortD;
/*****************************DIO_VoidInit***********************************/

uint8 Dio_PinInitArray[]={
		Dio_PinA0_init, Dio_PinA1_init, Dio_PinA2_init, Dio_PinA3_init,
		Dio_PinA4_init, Dio_PinA5_init, Dio_PinA6_init, Dio_PinA7_init,
		Dio_PinB0_init, Dio_PinB1_init, Dio_PinB2_init, Dio_PinB3_init,
		Dio_PinB4_init, Dio_PinB5_init, Dio_PinB6_init, Dio_PinB7_init,
		Dio_PinC0_init, Dio_PinC1_init, Dio_PinC2_init, Dio_PinC3_init,
		Dio_PinC4_init, Dio_PinC5_init, Dio_PinC6_init, Dio_PinC7_init,
		Dio_PinD0_init, Dio_PinD1_init, Dio_PinD2_init, Dio_PinD3_init,
		Dio_PinD4_init, Dio_PinD5_init, Dio_PinD6_init, Dio_PinD7_init
};

void DIO_voidInit(void)
{
	for(uint8 PinCount=Pin_A0;PinCount<=Pin_D7;PinCount++){
		DIO_voidSetPinChMode(PinCount,Dio_PinInitArray[PinCount]);
	}
}

void DIO_voidSetPinChMode(Pin_Type Copy_PinID, PinMode_type Copy_PinMode)
{
	Pin_Type Port_Index = Copy_PinID/8;
	Pin_Type Pin_Index  = Copy_PinID%8;
	switch(Copy_PinMode)
	{
	case OutPut_High :
		SET_BIT(*DIO_RegDDR[Port_Index] ,Pin_Index);
		SET_BIT(*DIO_RegPORT[Port_Index],Pin_Index);
		break;

	case OutPut_Low :
		SET_BIT(*DIO_RegDDR[Port_Index] ,Pin_Index);
		CLR_BIT(*DIO_RegPORT[Port_Index],Pin_Index);
		break;

	case InPut_Float :
		CLR_BIT(*DIO_RegDDR[Port_Index] ,Pin_Index);
		break;

	case InPut_PullUp :
		CLR_BIT(*DIO_RegDDR[Port_Index] ,Pin_Index);
		SET_BIT(*DIO_RegPORT[Port_Index],Pin_Index);
		break;
	default:
		//Report Error
		break;
	}
}

void DIO_voidWritePinChannel(Pin_Type Copy_PinID, PIN_VAL Copy_Var)
{
	Pin_Type Port_Index = Copy_PinID/8;
	Pin_Type Pin_Index  = Copy_PinID%8;
	switch (Copy_Var)
	{
	case Low :
		CLR_BIT(*DIO_RegPORT[Port_Index] ,Pin_Index);
		break;

	case High :
		SET_BIT(*DIO_RegPORT[Port_Index],Pin_Index);
		break;

	default :
		//Report Error
		break;
	}
}

void DIO_voidReadPinChannel(Pin_Type Copy_PinID, uint8* Copy_pBufferPtr)
{
	Pin_Type Port_Index = Copy_PinID / 8;
	Pin_Type Pin_Index  = Copy_PinID % 8;
	if (Copy_pBufferPtr != NULL )
	{
		*Copy_pBufferPtr = GET_BIT(*DIO_RegPIN[Port_Index],Pin_Index);
	}
	else
	{
		//Report Error
	}
}

void DIO_voidReadPortChannel(PORT_ID Copy_PortID, uint8* Copy_pBufferPtr)
{
	if (Copy_pBufferPtr != NULL )
	{
		*Copy_pBufferPtr = *DIO_RegPIN[Copy_PortID];
	}
	else
	{
		//Report Error
	}
}

void DIO_voidWritePortChannel(PORT_ID Copy_PortID, PORT_VAL Copy_Var)
{
	*DIO_RegPORT[Copy_PortID]= Copy_Var;
}

void DIO_voidWritePortWithMask(PORT_ID Copy_PortID, uint8 Copy_Mask, uint8 Copy_Data)
{
	*DIO_RegPORT[Copy_PortID] = ((*DIO_RegPORT[Copy_PortID])&Copy_Mask)|Copy_Data;
}
