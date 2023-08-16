/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: HAL			 			**************/
/***********		Component: CLCD			 		**************/
/***********		Version: 1.00		 			**************/
/***********		Date: 17-12-2022	 			**************/
/*****************************************************************/

#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"


#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"

static u8 u8SateSpecialCharIndx = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_LOW); /* Instruction Mode RS=0 */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW); /* Instruction Mode RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */



#if (CLCD_DATA_BITS_MODE == 4)
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN, GET_BIT(Copy_u8Command, 4));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN, GET_BIT(Copy_u8Command, 5));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN, GET_BIT(Copy_u8Command, 6));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN, GET_BIT(Copy_u8Command, 7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH); /* Disable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN, GET_BIT(Copy_u8Command, 0));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN, GET_BIT(Copy_u8Command, 1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN, GET_BIT(Copy_u8Command, 2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN, GET_BIT(Copy_u8Command, 3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(CLCD_DATA_BITS_MODE == 8)
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW); /* Disable LCD E=1 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void CLCD_voidSendData(u8 Copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RS_PIN , DIO_u8PIN_HIGH); /* Data Mode RS=1 */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_RW_PIN , DIO_u8PIN_LOW); /* Instruction Mode RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

#if (CLCD_DATA_BITS_MODE == 4)
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN, GET_BIT(Copy_u8Data, 4));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN, GET_BIT(Copy_u8Data, 5));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN, GET_BIT(Copy_u8Data, 6));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN, GET_BIT(Copy_u8Data, 7));
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_HIGH); /* Disable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D4_PIN, GET_BIT(Copy_u8Data, 0));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D5_PIN, GET_BIT(Copy_u8Data, 1));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D6_PIN, GET_BIT(Copy_u8Data, 2));
	DIO_u8SetPinValue(CLCD_DATA_PORT,CLCD_D7_PIN, GET_BIT(Copy_u8Data, 3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif(CLCD_DATA_BITS_MODE == 8)
	DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_U8Data);
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	DIO_u8SetPinValue(CLCD_CTRL_PORT , CLCD_E_PIN , DIO_u8PIN_LOW);
	_delay_ms(1); /* delay for processing Th = 13ns */
#endif
}

void CLCD_voidInit(void)
{
	/* Configure the direction for RS , E and RW pins as output pins */
	DIO_u8SetPinDirection(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_OUTPUT);
	_delay_ms(20);		/* LCD Power ON delay always > 15ms */

#if (CLCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	DIO_u8SetPinDirection(CLCD_DATA_PORT,CLCD_D4_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CLCD_DATA_PORT,CLCD_D5_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CLCD_DATA_PORT,CLCD_D6_PIN,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(CLCD_DATA_PORT,CLCD_D7_PIN,DIO_u8PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	CLCD_voidSendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	CLCD_voidSendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	CLCD_voidSendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(CLCD_DATA_BITS_MODE == 8)

	/* Configure the data port as output port */
	DIO_SetPortDirection(CLCD_DATA_PORT,DIO_u8PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	CLCD_voidSendCommand(TWO_LINE_LCD_Eight_BIT_MODE);
#endif

	CLCD_voidSendCommand(LCD_CURSOR_OFF);    /* cursor off */
	CLCD_voidSendCommand(LCD_CLEAR_COMMAND); /* clear LCD at the beginning */
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	u8 Local_u8Counter = 0;
	while(Copy_pcString[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_pcString[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void CLCD_voidGoToXY(u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	switch (Copy_u8XPos) {
	case 0:
		CLCD_voidSendCommand(128 + Copy_u8YPos);
		break;
	case 1:
		CLCD_voidSendCommand(192 + Copy_u8YPos);
		break;
	case 2:
		CLCD_voidSendCommand(256 + Copy_u8YPos);
		break;
	case 3:
		CLCD_voidSendCommand(320 + Copy_u8YPos);
		break;
	default:
		//
		break;

	}
}

void CLCD_voidSendStringGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos,const char* Copy_pcString)
{
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	CLCD_voidSendString(Copy_pcString);


}
void CLCD_voidWriteSpecialCharacter(u8* Copy_pu8Pattern , u8 Copy_u8PatternNumber , u8 Copy_u8XPos , u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAdress = 0;
	u8 Local_u8Iterator;
	u8SateSpecialCharIndx = 1;

	Local_u8CGRAMAdress = Copy_u8PatternNumber * 8;
	CLCD_voidSendCommand(Local_u8CGRAMAdress + 64);

	for(Local_u8Iterator = 0 ; Local_u8Iterator < 8 ; Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8Iterator]);
	}
	CLCD_voidGoToXY(Copy_u8XPos , Copy_u8YPos);
	CLCD_voidSendData(Copy_u8PatternNumber);
	u8SateSpecialCharIndx = 0;
}

void CLCD_voidSendNumber(u32 Copy_u32Number)
{
	u8 Local_u8DigitNumber;
	s8 Local_s8Counter = -1 , Local_s8Iterator;
	u8 Array_Number[CLCD_SIZE_OF_ARRAY];
	do
	{
		Local_s8Counter++;
		Local_u8DigitNumber = Copy_u32Number % 10;
		Array_Number[Local_s8Counter] = Local_u8DigitNumber + '0';
		Copy_u32Number /= 10;
	}while(Copy_u32Number != 0);
	for(Local_s8Iterator = Local_s8Counter; Local_s8Iterator >= 0; Local_s8Iterator--)
	{
		CLCD_voidSendData(Array_Number[Local_s8Iterator]);
	}
}

void CLCD_voidIntegerToString (u8 value)	// Display certain integer value on screen
{
	u8 number_str[16];
	itoa(value, number_str, 10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	CLCD_voidSendString(number_str);
}

void CLCD_voidClearScreen (void)
{
	CLCD_voidSendCommand(LCD_CLEAR_COMMAND);
}
