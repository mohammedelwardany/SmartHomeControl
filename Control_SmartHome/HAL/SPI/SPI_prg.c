/*
 * SPI_prg.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

/* UTILIES_LIB */
#include "LIB_STD_TYPES.h"
#include "LIB_BIT_MATH.h"

/*MCAL*/
#include "SPI_cfg.h"
#include "SPI_int.h"
#include "SPI_prv.h"

//Global Function to be passed to the ISR
void (*pfuncSPI_STCcomplete_ISR)(void);

/*
 * Pin Direction, Master SPI Direction, Slave SPI
 *     MOSI         User Defined        Input
 *     MISO         Input               User Defined
 *     SCK          User Defined        Input
 *     SS           User Defined        Input
 * */

void SPI_voidMasterInit(void)
{
	//Put MOSI as OutPut_High
	DIO_voidSetPinChMode(MOSI_PIN, OutPut_Low);

	//Put MISO as InPut_Float
	DIO_voidSetPinChMode(MISO_PIN, InPut_Float);

	//Put SCK as OutPut_High
	DIO_voidSetPinChMode(SCK_PIN, OutPut_Low);

	//Put the SS as OutPut_High
	DIO_voidSetPinChMode(SS_PIN, OutPut_Low);
	/*
	 * 1) Master
	 * 2) clk =focs/128
	 * 3) polarity = 0 and phase = 0
	 * 4) enable SPI
	 */
	SPCR |= INTERRUPT_ENABLE | (1<<SPE) | DATA_ORDER | (1<<MSTR) | SPI_MODE | OSCILLATOR_FREQUENCY_SPCR;
	SPSR |= OSCILLATOR_FREQUENCY_SPSR;
}

void SPI_voidSlaveInit(void)
{
	// Put MOSI as Input with pull-up
	DIO_voidSetPinChMode(MOSI_PIN, InPut_Float);

	// Put MISO as OutPut_High
	DIO_voidSetPinChMode(MISO_PIN, OutPut_Low);

	// Put SCK as Input (for slave mode)
	DIO_voidSetPinChMode(SCK_PIN, InPut_Float);

	// Put the SS as InPut_Float
	DIO_voidSetPinChMode(SS_PIN, InPut_Float);
	/*
	 * 1) Master
	 * 2) clk =focs/128
	 * 3) polarity = 0 and phase = 0
	 * 4) enable SPI
	 */
	SPCR |= INTERRUPT_ENABLE | (1<<SPE) | DATA_ORDER | (0<<MSTR) | SPI_MODE | OSCILLATOR_FREQUENCY_SPCR;
	SPSR |= OSCILLATOR_FREQUENCY_SPSR;
}

uint8 SPI_u8Tranceiver(uint8 Copy_u8data)
{
	SPDR = Copy_u8data ;
	while (GET_BIT(SPSR, SPIF) == 0);
	return SPDR;
}

void SPI_voidCallBackSTCcomplete(void(*ptr)(void))
{
	if(ptr != NULL)
	{
		pfuncSPI_STCcomplete_ISR = ptr;
	}
}

void __vector_12(void)
{
	pfuncSPI_STCcomplete_ISR();
}
