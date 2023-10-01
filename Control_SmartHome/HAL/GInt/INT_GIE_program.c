/*
 * 	INT_GIE_program.c
 *
 *  Created on: Sep 11, 2023
 *      Author: Emii
 */



/* UTILIES_LIB */
#include "LIB_STD_TYPES.h"
#include "LIB_BIT_MATH.h"

/*MCAL*/
#include "INT_GIE_interface.h"
#include "INT_GIE_private.h"

//***************************************************************************************//

void INT_GIE_voidEnable (void)
{
	SET_BIT(SREG,I);
}

//***************************************************************************************//

void INT_GIE_voidDisable(void)
{

	CLR_BIT(SREG ,I);
}


