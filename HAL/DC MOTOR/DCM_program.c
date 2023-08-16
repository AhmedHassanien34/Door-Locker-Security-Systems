/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: HAL			 			**************/
/***********		Component: DC_Motor		 		**************/
/***********		Version: 1.00		 			**************/
/***********		Date: 17-12-2022	 			**************/
/*****************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"

#include "DCM_config.h"
#include "DCM_interface.h"
#include "DCM_private.h"


void DCM_voidInit(void)
{
	/* Set The DC motor pins an output pins */
	DIO_u8SetPinDirection(DCM_PORT,DCM_PIN0,DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(DCM_PORT,DCM_PIN1,DIO_u8PIN_OUTPUT);


	/* Set initial value zero for The Dc motor */
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_LOW);

	/* Initial the time FAST PWM with Prescaler F_CPU_8 */
}

void DCM_voidCW(void)
{
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_HIGH);
}


void DCM_voidCCW(void)
{
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_HIGH);
}

void DCM_voidRotate( u8 Local_u8State )
{
	 /* Choose DC motor movement */
	if(Local_u8State == CW_STATE)
	{
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_HIGH);
	}
	else if(Local_u8State == CWW_STATE)
	{
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_HIGH);
	}
	else if(Local_u8State == STOP_STATE)
	{
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN0,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DCM_PORT,DCM_PIN1,DIO_u8PIN_LOW);
	}
}
