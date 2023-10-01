
#ifndef KEYPAD_HANDLER_V1_KEYPAD_CFG_H_
#define KEYPAD_HANDLER_V1_KEYPAD_CFG_H_
#include "DIO_int.h"
#define F_CPU	16000000




#define KEYPAD_ROW_1         Pin_C5
#define KEYPAD_ROW_2         Pin_C4
#define KEYPAD_ROW_3         Pin_C3
#define KEYPAD_ROW_4         Pin_C2

/***************************************************************************************/

#define KEYPAD_COLUMN_1      Pin_D7
#define KEYPAD_COLUMN_2      Pin_D6
#define KEYPAD_COLUMN_3      Pin_D5
#define KEYPAD_COLUMN_4      Pin_D3

#define KYP_ARR {{'7','8','9','/'}, {'4','5','6','*'}, {'1','2','3','-'}, {'C','0','=','+'}}

uint8 COL_ARR[4]={
		KEYPAD_COLUMN_1,KEYPAD_COLUMN_2,KEYPAD_COLUMN_3,KEYPAD_COLUMN_4
};

uint8 ROW_ARR[4]={
		KEYPAD_ROW_1,KEYPAD_ROW_2,KEYPAD_ROW_3,KEYPAD_ROW_4
};

/***************************************************************************************/

#define KEYPAD_ROWS_NO       (uint8)4
#define KEYPAD_COLUMNS_NO    (uint8)4

#define KEYPAD_NOT_PRESSED   '\0'

/***************************************************************************************/


#endif /* KEYPAD_HANDLER_V1_KEYPAD_CFG_H_ */
