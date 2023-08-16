/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: HAL			 			***********************/
/********************			Component: Keypad  			    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 16-12-2022	 			***********************/
/**************************************************************************************/

#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"

#include "DIO_register.h"

/***************************************************************************************************/
/****************************************Function Prototypes****************************************/



#if (N_COL == 3)

static u8 Keypad_4x3_adjustKeyNumber (u8 button_number);


#elif (N_COL == 4)

static u8 Keypad_4x4_adjustKeyNumber (u8 button_number);

#endif

void KPD_voidInit(void)
{
	// Setting Column pins to output
	DIO_u8SetPinDirection(KPD_PORT,KPD_COLUMN0_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_COLUMN1_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_COLUMN2_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(KPD_PORT,KPD_COLUMN3_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinValue(KPD_PORT,KPD_COLUMN0_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_COLUMN1_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_COLUMN2_PIN,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT,KPD_COLUMN3_PIN,DIO_u8PIN_HIGH);

	// Setting Row pins to input or input with pullup enabled
	DIO_u8SetPinDirection(KPD_PORT,KPD_ROW0_PIN,DIO_u8PIN_INPULLUP);
	DIO_u8SetPinDirection(KPD_PORT,KPD_ROW1_PIN,DIO_u8PIN_INPULLUP);
	DIO_u8SetPinDirection(KPD_PORT,KPD_ROW2_PIN,DIO_u8PIN_INPULLUP);
	DIO_u8SetPinDirection(KPD_PORT,KPD_ROW3_PIN,DIO_u8PIN_INPULLUP);
}



u8 KPD_u8GetPressedKey(void)
{
	u8 row, col;
	while(1)
	{
		for (col = 0; col < N_COL; col++)
		{
			KEYPAD_PORT_DIR = (0b00010000<< col);

			KEYPAD_PORT_OUT = (~(0b00010000<< col));
			for (row = 0; row < N_ROW; row++)
			{
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN,row))
				{
#if (N_COL == 3)

					return Keypad_4x3_adjustKeyNumber (((row*N_COL)+col+1));
#elif (N_COL == 4)

					return Keypad_4x4_adjustKeyNumber (((row*N_COL)+col+1));

#endif
				}
			}
		}
	}
}

#if (N_COL == 3)

static u8 Keypad_4x3_adjustKeyNumber (u8 button_number)
{
	switch (button_number)
	{
		case 10:
		return '*'; //	ASCII code of *
		break;
		case 11:
		return 0;
		break;
		case 12:
		return '#'; //	ASCII code of #
		break;
		default:
		return button_number;
		break;
	}
}


#elif (N_COL == 4)

 static u8 Keypad_4x4_adjustKeyNumber (u8 button_number)
{
	switch (button_number)
	{
		case 1:		return '!';
		break;
		case 2:		return '@';
		break;
		case 3:		return '#';
		break;
		case 4:		return '$';
		break;
		case 5:		return '*';
		break;
		case 6:		return '4';
		break;
		case 7:		return '7';
		break;
		case 8:		return '1';
		break;
		case 9:		return '0';
		break;
		case 10:	return '5';
		break;
		case 11:	return '8';
		break;
		case 12:	return '2';
		break;
		case 13:	return '#';
		break;
		case 14:	return '6';
		break;
		case 15:	return '9';
		break;
		case 16:	return '3';
		break;
	}
}
#endif
/*u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY , Local_u8ColumnIdx , Local_u8RowIdx , Local_u8PinsState;
	static u8 Local_u8Arr[ROW_NUM][COLUMN_NUM] = KPD_ARR_VAL;
	static u8 Local_u8KPDColumnArr[COLUMN_NUM] = {KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8KPDROWArr[ROW_NUM] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};
	while (1)
	{
	for(Local_u8ColumnIdx = 0; Local_u8ColumnIdx < COLUMN_NUM; Local_u8ColumnIdx++)
	{
		// Activate current column
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIdx],DIO_u8PIN_LOW);
		for(Local_u8RowIdx = 0; Local_u8RowIdx < ROW_NUM; Local_u8RowIdx++)
		{
			// Read the current row
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDROWArr[Local_u8RowIdx],&Local_u8PinsState);

			// Check if switch is pressed
			if(DIO_u8PIN_LOW == Local_u8PinsState)
			{
				//_delay_ms(1000); // New
				Local_u8PressedKey = Local_u8Arr[Local_u8RowIdx][Local_u8ColumnIdx];
				// Polling(busy waiting) untill the key is released
				while(DIO_u8PIN_LOW == Local_u8PinsState)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDROWArr[Local_u8RowIdx],&Local_u8PinsState);
				}
				return Local_u8PressedKey;
			}
		}
		// Deactivate the current column
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIdx],DIO_u8PIN_HIGH);
	}
	return Local_u8PressedKey;
	}*/
