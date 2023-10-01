/*
 * SPI_cfg.h
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

#ifndef MCAL_SPI_V1_SPI_CFG_H_
#define MCAL_SPI_V1_SPI_CFG_H_

#include "DIO_int.h"

#define SS_PIN								  Pin_B4
#define MOSI_PIN						      Pin_B5
#define MISO_PIN						      Pin_B6
#define SCK_PIN								  Pin_B7

//in SPCR
/*Select ENABLED or
 *       DISABLED*/
#define INTERRUPT_ENABLE      				  DISABLED

/*Select LSB_TRANSMITTED_FIRST or
 *       MSB_TRANSMITTED_FIRST*/
#define DATA_ORDER     					      LSB_TRANSMITTED_FIRST

/*Select MODE_0 or
 *       MODE_1 or
 *       MODE_2 or
 *       MODE_3*/
#define SPI_MODE                  			  MODE_0

/*Select NORMAL_SPEED_FOSC_OVER_4   or
 *       NORMAL_SPEED_FOSC_OVER_16  or
 *       NORMAL_SPEED_FOSC_OVER_64  or
 *       NORMAL_SPEED_FOSC_OVER_128 or
 *       DOUBLE_SPEED_FOSC_OVER_2   or
 *       DOUBLE_SPEED_FOSC_OVER_8   or
 *       DOUBLE_SPEED_FOSC_OVER_32  or
 *       DOUBLE_SPEED_FOSC_OVER_64
 * */
#define OSCILLATOR_FREQUENCY				  NORMAL_SPEED_FOSC_OVER_4



#endif /* MCAL_SPI_V1_SPI_CFG_H_ */
