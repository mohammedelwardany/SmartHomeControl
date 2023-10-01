/*
 * ADC_cfg.h
 *
 *  Created on: Sep 15, 2023
 *      Author: Emii
 */

#ifndef MCAL_ADC_V1_ADC_CFG_H_
#define MCAL_ADC_V1_ADC_CFG_H_

#include "ADC_int.h"

/* Choose from the following the desired Prescaler
 * Prescaler2, Prescaler_2, Prescaler_4, Prescaler_8,
 * Prescaler_16, Prescaler_32, Prescaler_64, Prescaler_128*/
#define ADC_PRESCALER 				Prescaler_128 //15K SPS between Freq Source

/* Choose from the following the desired Vref AREF, AVCC, Internal_Vref */
#define VOLTAGE_REFERENCE  			Internal_Vref

/* Adjustment -> Right_Adjust or Left_Adjust */
#define ADC_ADJUST	 				Right_Adjust

/* Triggering -> Auto_Triggered or Single_Conversion */
#define ADC_TRIGGER_SOURCE	 		Single_Conversion

/* Auto_Triggered Modes */
#define ADC_AUTO_TRIGGER_SOURCE	 	Free_Running_mode

/*Scan Group*/
#define MAX_NUMBER_OF_CHANNELS		4
#define SG0Channel0				    ADC_Channel_0
#define SG0Channel1				    ADC_Channel_1
#define SG0Channel2				    ADC_Channel_4
#define SG0Channel3				    ADC_Channel_5

#define SG1Channel0				    ADC_Channel_2
#define SG1Channel1				    ADC_Channel_3
#define SG1Channel2				    ADC_Channel_6
#define SG1Channel3				    ADC_Channel_7


#endif /* MCAL_ADC_V1_ADC_CFG_H_ */
