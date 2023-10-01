/*
 * ADC_int.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Emii
 */

#ifndef MCAL_ADC_V1_ADC_INT_H_
#define MCAL_ADC_V1_ADC_INT_H_

#include "ADC_prv.h"

//***************************************************************************************//

							/*ADCSRA Enums to be used with*/
//For ADPS2:0: ADC Prescaler Select Bits in ADCSRA
typedef enum
{
    Prescaler2,
	Prescaler_2,
	Prescaler_4,
	Prescaler_8,
	Prescaler_16,
	Prescaler_32,
	Prescaler_64,
	Prescaler_128
}ADC_Prescaler_t;

//For Triggering Source -> ADATE: ADC Auto Trigger Enable Bit in ADCSRA
typedef enum
{
    Single_Conversion,
	Auto_Triggered
}ADC_TriggerSource_t;

//***************************************************************************************//

								/*ADMUX Enums to be used with*/
//For Voltage REF --> REFS1 = 0 REFS0 = 1 in ADMUX
typedef enum
{
    AREF = 0<<ADMUX_BIT_6_REFS0, //External
	AVCC = 1<<ADMUX_BIT_6_REFS0, //internal 5v
	Internal_Vref = 3<<ADMUX_BIT_6_REFS0 //2.65v
}ADC_Voltage_Reference_t;

//For ADLAR Left adjust or Right in ADMUX
typedef enum
{
	Right_Adjust = 0<<5,
	Left_Adjust = 1<<5
}ADC_ADLAR_t;

//For Channel Selection ADMUX
typedef enum
{
    ADC_Channel_0,
	ADC_Channel_1,
	ADC_Channel_2,
	ADC_Channel_3,
	ADC_Channel_4,
	ADC_Channel_5,
	ADC_Channel_6,
	ADC_Channel_7
}ADC_Channel_t;

//***************************************************************************************//

							/*SFIOR Enums to be used with*/
//For Auto Trigger Source Selection in SFIOR
typedef enum
{
	Free_Running_mode = 0<<5,
	Analog_Comparator = 1<<5,
	External_Interrupt_Request_0 = 2<<5,
	Timer_Counter0_Compare_Match = 3<<5,
	Timer_Counter0_Overflow = 4<<5,
	Timer_Counter_Compare_Match_B = 5<<5,
	Timer_Counter1_Overflow = 6<<5,
	Timer_Counter1_Capture_Event = 7<<5
}ADC_Auto_Trigger_Source_t;

//***************************************************************************************//
typedef enum
{
    Scan_Group0, //External
	Scan_Group1 //internal 5v
}ADC_Scan_Group_t;

/*Initialization Function*/
void ADC_voidADCinit (void);

/*Single Channel Reading Function Synchronous*/
uint16 ADC_u16ADCSyncSingleChannelRead(ADC_Channel_t Copy_u8channelNo);

/*Multiple Channels Reading Function Synchronous*/
void ADC_voidSyncRead(ADC_Scan_Group_t Copy_pScanGroup, uint16*Copy_u16pBuffer);

/*Multiple Channels Reading Function ASynchronous*/
void ADC_voidASyncRead(ADC_Scan_Group_t Copy_pScanGroup, void(*Copy_ArrPPFunc[])(void), uint16*Copy_u16pBuffer);

/*Vector Table -> Vector Number = 17 -Representing ADC Conversion Complete*/
void __vector_16(void) __attribute__((signal));

#endif /* MCAL_ADC_V1_ADC_INT_H_ */
