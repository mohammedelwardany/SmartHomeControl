/*
 * I2C_prg.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */

/* UTILES_LIB */
#include "LIB_STD_TYPES.h"
#include "LIB_BIT_MATH.h"

/* MCAL */
#include "I2C_int.h"
#include "I2C_prv.h"

void TWI_voidInitMaster(uint8 Copy_u8Add)
{
	//Select Master Address assigning Address done with TWAR
	if(Copy_u8Add<128)
	{
		TWAR = Copy_u8Add<<1;
	}

	// Set Prescaller = 1 >> Set Freq. = 400KHZ
	//TWBR selects the division factor for the bit rate generator
	TWBR = 12;
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);

	// Enable ACK
	SET_BIT(TWCR,TWEA);

	// Enable TWI peripheral
	SET_BIT(TWCR,TWEN);
}

void TWI_voidSendStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR,TWSTA);

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);

	// Wait for the flag polling
	while(0 == GET_BIT(TWCR,TWINT));

	// Check ACK = SC ACK nt2kd enha sam3et
	while(TWI_STATUS_VALUE != TWI_START_CONDITION_ACK);
}

void TWI_voidSendRepStartCondition(void)
{
	// Request Start Condition
	SET_BIT(TWCR,TWSTA);

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);

	// Wait for the flag 34an nt2kd enha 5elst
	while(0 == GET_BIT(TWCR,TWINT));

	// Check ACK = Repeated SC ACK 34an nt2kd enha 5elst sa7
	while(TWI_STATUS_VALUE != TWI_REP_START_CONDITION_ACK);
}

void TWI_voidSendStopCondition(void)
{
	//Mlhash Status Code h request w a clear flag bas
	// Request Stop Condition
	SET_BIT(TWCR,TWSTO);

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);
}

//the following functions are similar
void TWI_voidSendSlaveAddWithWrite(uint8 Copy_u8SlaveAdd)
{
	if(Copy_u8SlaveAdd<128)
	{
		//34an yb3at ay haga 3la l bus lazm ab3t 3la Data Reg so bnb3t l slave address l assigned fo2
		//3la l data reg
		//shifting 34an l frame kan 7 bit address
		TWDR = Copy_u8SlaveAdd<<1;

		// Select write operation
		CLR_BIT(TWDR,0);

		// Clear SC bit -> TWSTA must be cleared by software when the START condition has been transmitted.
		//Restriction zeyada lw mat3mltsh l b3dha msh hatet3ml
		CLR_BIT(TWCR,TWSTA);

		// Clear flag to start current job
	    SET_BIT(TWCR,TWINT);

	    // Wait for the flag
	    while(0 == GET_BIT(TWCR,TWINT));

	    // Check ACK = Master transmit ( slave address + Write request ) ACK
	    while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_WRITE_ACK);
	}
	else
	{
		//Report Error
	}
}

void TWI_voidSendSlaveAddWithRead(uint8 Copy_u8SlaveAdd)
{
	if(Copy_u8SlaveAdd<128)
	{
		TWDR = Copy_u8SlaveAdd<<1;

		// Select read operation
		SET_BIT(TWDR,0);

		// Clear SC bit
		CLR_BIT(TWCR,TWSTA);

		// Clear flag to start current job
	    SET_BIT(TWCR,TWINT);

	    // Wait for the flag
	    while(0 == GET_BIT(TWCR,TWINT));

	    // Check ACK = Master transmit ( slave address + Read request ) ACK
	    while(TWI_STATUS_VALUE != TWI_SLAVE_ADDRESS_READ_ACK);
	}
	else
	{
		//Do Nothing
	}
}

void TWI_voidSendMasterDataByte(uint8 Copy_u8TxData)
{
	// Write Data into data register
	TWDR = Copy_u8TxData;

	// Clear flag to start current job
	SET_BIT(TWCR,TWINT);

	// Wait for the flag
	while(0 == GET_BIT(TWCR,TWINT));

	// Check ACK = Master transmit data ACK
	while(TWI_STATUS_VALUE != TWI_MASTER_DATA_TRANSMIT_ACK);
}

void TWI_voidRecieveMasterDataByte(uint8* Copy_pu8RxData)
{
	if(Copy_pu8RxData != NULL)
	{
		// Clear flag to start current job
	    SET_BIT(TWCR,TWINT);

	    // Wait for the flag
	    while(0 == GET_BIT(TWCR,TWINT));

		// Check ACK = Master received data with ACK
	    while(TWI_STATUS_VALUE != TWI_MASTER_DATA_RECIEVE_ACK);

		// Read Data from data register
		*Copy_pu8RxData = TWDR;
	}
}
