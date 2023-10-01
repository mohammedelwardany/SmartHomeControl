/*
 * ADC_prg.c
 *
 *  Created on: Sep 15, 2023
 *      Author: Emii
 */

#include "LIB_STD_TYPES.h"
#include "LIB_BIT_MATH.h"
#include "ADC_int.h"
#include "ADC_prv.h"
#include "ADC_cfg.h"

#define ADMUX_VREF_MUSK            					    0b00111111
#define ADMUX_ADLAR_MUSK								0b11011111
#define ADMUX_CHANNEL_SELECTION_MUSK					0b11100000

#define ADCSRA_PRESCALER_MUSK           			    0b11111000

#define SFIOR_AUTO_TRIGGER_SOURCE_MUSK           		0b00011111

/*Global Array Pointer to Function to be passed to the ISR*/
void (*pfuncADC_ISR[4])(void);
ADC_Channel_t Global_pScanGroup;
uint16* Global_u16pBuffer;
uint8 Global_u8Counter = 0;

uint8 ADC_ScanGroups0[4]={SG0Channel0,SG0Channel1,SG0Channel2,SG0Channel3};
uint8 ADC_ScanGroups1[4]={SG1Channel0,SG1Channel1,SG1Channel2,SG1Channel3 };

uint8 * ptr[2]= {ADC_ScanGroups0,ADC_ScanGroups1};

/*Initialization Function*/
void ADC_voidADCinit (void)
{
	/* Prescaler DIVISION FACTOR */
	ADCSRA = (ADCSRA & ADCSRA_PRESCALER_MUSK) | ADC_PRESCALER;

	/* Voltage REF */
	ADMUX = (ADMUX & ADMUX_VREF_MUSK) | VOLTAGE_REFERENCE;

	/* Left Adjust mode set ADLAR = 1*/
	ADMUX = (ADMUX & ADMUX_ADLAR_MUSK) | ADC_ADJUST;

	/* Triggering Source*/
#if ADC_TRIGGER_SOURCE == Single_Conversion
	CLR_BIT(ADCSRA,ADCSRA_BIT_5_ADATE);

#elif ADC_TRIGGER_SOURCE == Auto_Triggered
	SET_BIT(ADCSRA,ADCSRA_BIT_5_ADATE);
	/*Auto Trigger Source Selection*/
	SFIOR = (SFIOR & SFIOR_AUTO_TRIGGER_SOURCE_MUSK) | ADC_AUTO_TRIGGER_SOURCE;
#endif

	/* ADC Enable */
	SET_BIT(ADCSRA,ADCSRA_BIT_7_ADEN);
}

/*Single Channel Reading Function*/
uint16 ADC_u16ADCSyncSingleChannelRead(ADC_Channel_t Copy_u8channelNo)
{
	uint16 Local_u16DigitalRead ;

	/* Channel Select */
	ADMUX = (ADMUX & ADMUX_CHANNEL_SELECTION_MUSK) | Copy_u8channelNo;

#if ADC_TRIGGER_SOURCE == Single_Conversion
	/*Start Conversion BIT_6 set it to 1*/
	SET_BIT(ADCSRA,ADCSRA_BIT_6_ADSC);

	/*Wait until the conversion finished*/
	while (GET_BIT(ADCSRA,4)== 0);

	/* Clear the Flag*/
	SET_BIT(ADMUX,ADCSRA_BIT_4_ADIF);

#elif ADC_TRIGGER_SOURCE == Auto_Triggered
	/* it's Auto Triggered*/

#endif

	/*Read ADC Value */
#if ADC_ADJUST == Right_Adjust
	Local_u16DigitalRead = ADC ;
#elif ADC_ADJUST == Left_Adjust
	Local_u16DigitalRead = ADCH ;
#endif

	/*return the value*/
	return Local_u16DigitalRead;
}

/*Multiple Channels Reading Function Synchronous*/
void ADC_voidSyncRead(ADC_Scan_Group_t Copy_pScanGroup, uint16*Copy_u16pBuffer)
{
	for (uint8 Local_u8ChannelIndex = 0; Local_u8ChannelIndex < MAX_NUMBER_OF_CHANNELS; Local_u8ChannelIndex++) {
		/* Store the ADC value in the buffer */
		Copy_u16pBuffer[Local_u8ChannelIndex] = ADC_u16ADCSyncSingleChannelRead( ptr[Copy_pScanGroup][Local_u8ChannelIndex] );
		//Copy_u16pBuffer[Local_u8iterator] = ADC_u16ADCSyncSingleChannelRead(Copy_pScanGroup[Local_u8iterator]);
	}
}

/*Multiple Channels Reading Function ASynchronous*/
void ADC_voidASyncRead(ADC_Scan_Group_t Copy_pScanGroup, void(*Copy_ArrPPFunc[4])(void), uint16*Copy_u16pBuffer)
{
	Global_u16pBuffer = Copy_u16pBuffer;
	Global_pScanGroup = Copy_pScanGroup;
	/*Setting the call back function to the global pointer to function*/
	for (uint8 i = 0; i < MAX_NUMBER_OF_CHANNELS; i++) {
		pfuncADC_ISR[i] = Copy_ArrPPFunc[i];
	}
	/* Channel Select */
	ADMUX = (ADMUX & ADMUX_CHANNEL_SELECTION_MUSK) | (ptr[Global_pScanGroup][0]);
	/*ADC Interrupt Enable*/
	SET_BIT(ADCSRA,ADCSRA_BIT_3_ADIE);
	SET_BIT(ADCSRA,ADCSRA_BIT_6_ADSC);

}

/*Setting the global pointer to function to the ISR*/
void __vector_16(void)
{
	/* Store the ADC value in the buffer */
#if ADC_ADJUST == Right_Adjust
	Global_u16pBuffer[Global_u8Counter] = ADC ;
#elif ADC_ADJUST == Left_Adjust
	Global_u16pBuffer[Global_u8Counter] = ADCH ;
#endif

	/* Call the user-defined callback function */
	if(pfuncADC_ISR[Global_u8Counter] != NULL)
	{
		pfuncADC_ISR[Global_u8Counter]();
	}

	/*Increase the counter*/
	Global_u8Counter++;

	if(Global_u8Counter == MAX_NUMBER_OF_CHANNELS)
	{
		Global_u8Counter = 0;
	}

	/* Start the Next Channel Reading */
	/* Channel Select */
	ADMUX = (ADMUX & ADMUX_CHANNEL_SELECTION_MUSK) | (ptr[Global_pScanGroup][Global_u8Counter]);
	SET_BIT(ADCSRA,ADCSRA_BIT_6_ADSC);

}
