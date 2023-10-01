/*
 * MDIO_config.h
 *
 *  Created on: Sep 8, 2023
 *      Author: Emii
 */

#ifndef MCAL_DIO_V2_DIO_CFG_H_
#define MCAL_DIO_V2_DIO_CFG_H_

#include "DIO_int.h"

								/*Linking Time Configuration*/

#define Dio_PinA0_init    InPut_PullUp
#define Dio_PinA1_init	  InPut_PullUp
#define Dio_PinA2_init	  OutPut_Low
#define Dio_PinA3_init    OutPut_Low
#define Dio_PinA4_init    OutPut_Low
#define Dio_PinA5_init    OutPut_Low
#define Dio_PinA6_init	  OutPut_Low
#define Dio_PinA7_init    OutPut_Low

#define Dio_PinB0_init    OutPut_Low
#define Dio_PinB1_init    OutPut_Low
#define Dio_PinB2_init    OutPut_Low
#define Dio_PinB3_init    OutPut_Low
#define Dio_PinB4_init	  OutPut_Low
#define Dio_PinB5_init    OutPut_Low
#define Dio_PinB6_init    OutPut_Low
#define Dio_PinB7_init    OutPut_Low

#define Dio_PinC0_init    OutPut_High
#define Dio_PinC1_init    OutPut_High
#define Dio_PinC2_init    OutPut_High
#define Dio_PinC3_init    OutPut_High
#define Dio_PinC4_init    OutPut_High
#define Dio_PinC5_init	  OutPut_High
#define Dio_PinC6_init	  OutPut_High
#define Dio_PinC7_init	  OutPut_High

#define Dio_PinD0_init	  InPut_PullUp
#define Dio_PinD1_init	  InPut_PullUp
#define Dio_PinD2_init	  InPut_PullUp
#define Dio_PinD3_init	  InPut_PullUp
#define Dio_PinD4_init	  InPut_PullUp
#define Dio_PinD5_init	  OutPut_Low
#define Dio_PinD6_init	  InPut_Float
#define Dio_PinD7_init	  InPut_PullUp

#endif /* MCAL_DIO_V2_DIO_CFG_H_ */
