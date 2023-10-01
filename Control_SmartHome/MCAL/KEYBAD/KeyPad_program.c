#define F_CPU	16000000



#include "KeyPad_Config.h"
#include "KeyPad_interface.h"
#include "LIB_STD_TYPES.h"
#include "DIO_int.h"
#include"util/delay.h"

void KEYPAD_uint8Init(void)
{
	//Set rows as input
	DIO_voidSetPinChMode(KEYPAD_COLUMN_1 , InPut_PullUp);
	DIO_voidSetPinChMode(KEYPAD_COLUMN_2 , InPut_PullUp);
	DIO_voidSetPinChMode(KEYPAD_COLUMN_3 , InPut_PullUp);
	DIO_voidSetPinChMode(KEYPAD_COLUMN_4 , InPut_PullUp);

	//Set Columns as output
	//Deactivate for all columns by setting it to High
	DIO_voidSetPinChMode(KEYPAD_ROW_1 , OutPut_High);
	DIO_voidSetPinChMode(KEYPAD_ROW_2 , OutPut_High);
	DIO_voidSetPinChMode(KEYPAD_ROW_3 , OutPut_High);
	DIO_voidSetPinChMode(KEYPAD_ROW_4 , OutPut_High);
}

uint8 KEYPAD_uint8GetPressedKey(void)
{
	uint8 Local_uint8PressedSwitch = KEYPAD_NOT_PRESSED;
	uint8 Local_uint8aKeyPadMap[KEYPAD_ROWS_NO][KEYPAD_COLUMNS_NO] = KYP_ARR;
	uint8 Local_uint8CurrentCol;
	uint8 Local_uint8CurrentRow;
	uint8 Local_uint8CurrentColStatus;

	for (Local_uint8CurrentRow = 0;
			Local_uint8CurrentRow < KEYPAD_ROWS_NO ;
			Local_uint8CurrentRow++)
	{
		/*activate the current column*/
		DIO_voidWritePinChannel(ROW_ARR[Local_uint8CurrentRow],Low);

		for (Local_uint8CurrentCol = 0 ;
				Local_uint8CurrentCol < KEYPAD_COLUMNS_NO ;
				Local_uint8CurrentCol++)
		{
			/*Get Row Value*/
			DIO_voidReadPinChannel(COL_ARR[Local_uint8CurrentCol] , &Local_uint8CurrentColStatus);
			/*If Switch is pressed */
			if (Local_uint8CurrentColStatus == Low) //34an e7na pull up
			{
				_delay_ms(25);
				/*Wait For Debouncing*/
				/*If Switch is pressed */

				DIO_voidReadPinChannel(COL_ARR[Local_uint8CurrentCol] , &Local_uint8CurrentColStatus);

				if (Local_uint8CurrentColStatus == Low) //34an e7na pull up
				{
								Local_uint8PressedSwitch = Local_uint8aKeyPadMap[Local_uint8CurrentRow][Local_uint8CurrentCol];
				}
				/* the switch which is in this row and that column is pressed*/
			}
		}
		/*Deactivate the column*/
		DIO_voidWritePinChannel(ROW_ARR[Local_uint8CurrentRow],High);

	}

	return Local_uint8PressedSwitch ;
}


