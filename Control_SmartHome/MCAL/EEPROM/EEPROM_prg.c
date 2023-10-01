/*
 * EEPROM_prg.c
 *
 *  Created on: Sep 28, 2023
 *      Author: Emii
 */
#define F_CPU	16000000



/* UTILES_LIB */
#include "LIB_STD_TYPES.h"
#include "LIB_BIT_MATH.h"
#include <util/delay.h>

/* MCAL */
#include "I2C_int.h"

/* HAL */
#include "EEPROM_int.h"
#include "EEPROM_prv.h"

void EEPROM_voidInit(void)
{
	TWI_voidInitMaster(255);
}

void EEPROM_voidWriteByte(uint16 Copy_u16WordAddress, uint8 Copy_u8Data)
{
	uint8 local_u8Address = (Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;

	// Send start condition
	TWI_voidSendStartCondition();

	// Send slave address with write operation
	TWI_voidSendSlaveAddWithWrite(local_u8Address);

	// Send word address - Byte Address
	TWI_voidSendMasterDataByte((uint8)Copy_u16WordAddress);

	// Send byte data
	TWI_voidSendMasterDataByte(Copy_u8Data);

	// Send stop condition
	TWI_voidSendStopCondition();

	// Self-timed Write Cycle delay
	_delay_ms(5);
}

void EEPROM_voidReadByte(uint16 Copy_u16WordAddress, uint8* Copy_pu8RxData)
{
	if(Copy_pu8RxData != NULL)
	{
		uint8 local_u8Address = (Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS;

		// Send start condition
		TWI_voidSendStartCondition();

		// Send slave address with write operation
		TWI_voidSendSlaveAddWithWrite(local_u8Address);

		// Send word address
		TWI_voidSendMasterDataByte((uint8)Copy_u16WordAddress);

		// Send Repeated start condition
		TWI_voidSendRepStartCondition();

		// Send slave address with read operation
		TWI_voidSendSlaveAddWithRead(local_u8Address);

		// Read byte data
		TWI_voidRecieveMasterDataByte(Copy_pu8RxData);

		// Send stop condition
		TWI_voidSendStopCondition();

		// Self-timed Cycle delay
		_delay_ms(5);
	}
}

//Task
void EEPROM_voidWritePage(uint16 Copy_u16WordAddress,uint8 Copy_u8size,uint8 *Copy_u8TransmitData)
{
	uint8 i = 0;
	uint8 local_u8Address = (Copy_u16WordAddress >> 8) | EEPROM_FIXED_ADDRESS;
	// Send start condition
	TWI_voidSendStartCondition();
	// Send slave address with write operation
	TWI_voidSendSlaveAddWithWrite(local_u8Address);
	// Send word address - Byte Address
	TWI_voidSendMasterDataByte((uint8)Copy_u16WordAddress);
	for (i = 0; i < Copy_u8size; i++)
	{
		// Send byte data
		TWI_voidSendMasterDataByte(Copy_u8TransmitData[i]);
	}
	// Send stop condition
	TWI_voidSendStopCondition();

	// Self-timed Write Cycle delay
	_delay_ms(5);
}

void EEPROM_voidReadPage(uint16 Copy_u16WordAddress,uint8 Copy_u8size,uint8* Copy_u8pRecievedData)
{
	uint8 Local_u8Counter =0;
	if ( (Copy_u8pRecievedData !=NULL) && (Copy_u8size <= 16) )
	{
		uint8 local_u8Address;
		local_u8Address = ((Copy_u16WordAddress>>8)|EEPROM_FIXED_ADDRESS);
		// Send start condition
		TWI_voidSendStartCondition();
		// Send slave address with write operation
		TWI_voidSendSlaveAddWithWrite(local_u8Address);
		// Send word address
		TWI_voidSendMasterDataByte((uint8)Copy_u16WordAddress);
		// Send Repeated Start Condition
		TWI_voidSendRepStartCondition();
		// Send slave address with read operation
		TWI_voidSendSlaveAddWithRead(local_u8Address);
		for (Local_u8Counter = 0; Local_u8Counter < Copy_u8size; Local_u8Counter++)
		{
			// Read byte data
			TWI_voidRecieveMasterDataByte(&Copy_u8pRecievedData[Local_u8Counter]);
		}
		// Send stop condition
		TWI_voidSendStopCondition();

		// Self-timed Write Cycle delay
		_delay_ms(5);
	}
}
