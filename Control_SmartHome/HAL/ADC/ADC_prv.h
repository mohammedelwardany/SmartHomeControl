/*
 * ADC_prv.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Emii
 */

#ifndef MCAL_ADC_V1_ADC_PRV_H_
#define MCAL_ADC_V1_ADC_PRV_H_

			/* ADC Multiplexer Selection Register – ADMUX */
#define ADMUX 	*((volatile uint8*)0x27) 	// ADC Multiplexer Register
#define ADMUX_BIT_0_MUX0				0 //Bit 0 – MUX0: Analog Channel and Gain Selection Bit
#define ADMUX_BIT_1_MUX1				1 //Bit 1 – MUX1: Analog Channel and Gain Selection Bit
#define ADMUX_BIT_2_MUX2				2 //Bit 2 – MUX2: Analog Channel and Gain Selection Bit
#define ADMUX_BIT_3_MUX3				3 //Bit 3 – MUX3: Analog Channel and Gain Selection Bit
#define ADMUX_BIT_4_MUX4				4 //Bit 4 – MUX4: Analog Channel and Gain Selection Bit
#define ADMUX_BIT_5_ADLAR				5 //Bit 5 – ADLAR: ADC Left Adjust Result
#define ADMUX_BIT_6_REFS0				6 //Bit 6 – REFS0: Reference Selection Bits
#define ADMUX_BIT_7_REFS1				7 //Bit 7 – REFS1: Reference Selection Bits

			/*ADC Control and Status Register A – ADCSRA*/
#define ADCSRA 	*((volatile uint8*)0x26) 	// ADC Control And Status Register
#define ADCSRA_BIT_0_ADPS0				0 //Bit 0 – ADPS0: ADC Prescaler Select Bit
#define ADCSRA_BIT_1_ADPS1				1 //Bit 1 – ADPS1: ADC Prescaler Select Bit
#define ADCSRA_BIT_2_ADPS2				2 //Bit 2 – ADPS2: ADC Prescaler Select Bit
#define ADCSRA_BIT_3_ADIE				3 //Bit 3 – ADIE: ADC Interrupt Enable
#define ADCSRA_BIT_4_ADIF				4 //Bit 4 – ADIF: ADC Interrupt Flag
#define ADCSRA_BIT_5_ADATE				5 //Bit 5 – ADATE: ADC Auto Trigger Enable
#define ADCSRA_BIT_6_ADSC				6 //Bit 6 – ADSC: ADC Start Conversion
#define ADCSRA_BIT_7_ADEN				7 //Bit 7 – ADEN: ADC Enable

			  /*Special Function IO Register – SFIOR*/
#define SFIOR   *((volatile uint8*)0x50)
#define SFIOR_BIT_4_ACME				4 //Bit 4 – ADIF: ADC Interrupt Flag
#define SFIOR_BIT_5_PUD					5 //Bit 5 – ADTS0: ADC Auto Trigger Source
#define SFIOR_BIT_6_PSR2				6 //Bit 6 – ADTS1: ADC Auto Trigger Source
#define SFIOR_BIT_7_PSR10				7 //Bit 7 – ADTS2: ADC Auto Trigger Source

				/*The ADC Data Register – ADCL and ADCH*/
#define ADCH 	*((volatile uint8*)0x25) 	// ADC High Register
#define ADCL 	*((volatile uint8*)0x24) 	// ADC Low Register
#define ADC	    *((volatile uint16*)0x24) 	// ADC High and Low Register


#endif /* MCAL_ADC_V1_ADC_PRV_H_ */
