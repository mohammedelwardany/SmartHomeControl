/*
 * 	INT_GIE_private.h
 *
 *  Created on: Sep 11, 2023
 *      Author: Emii
 */

#ifndef _INT_REG_H
#define _INT_REG_H
#define F_CPU	16000000
/* SREG -- FOR ACCESSING THE GIE */
#define SREG      (*((volatile uint8*)0x5F))

/*PIN 7 IS THE GIE*/
#define I   (uint8)7

#endif
