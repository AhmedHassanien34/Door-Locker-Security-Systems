/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: APP			 			***********************/
/********************			Component: Microwave_RTOS		***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 15-8-2023	 				***********************/
/**************************************************************************************/

/********************************************************************************************/
/* Include libraries                                                                        */
/********************************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include <util/delay.h>

/********************************************************************************************/
/* Include Interface Files in MCAL                                                          */
/********************************************************************************************/
#include "DIO_interface.h"

/********************************************************************************************/
/* Include Interface Files in HAL                                                           */
/********************************************************************************************/
#include "KPD_interface.h"
#include "CLCD_interface.h"
#include "DCM_interface.h"
#include "LED_interface.h"

#define EEPROM_Status_Flag        0x20
#define EEPROM_PASSWORD_LOCATION1 0x21
#define EEPROM_PASSWORD_LOCATION2 0x22
#define EEPROM_PASSWORD_LOCATION3 0x23
#define EEPROM_PASSWORD_LOCATION4 0x24
#define First_Use                 0XFF
#define Entered_The_Home          0x00
#define Max_Tries                 3


int main(void)
{
	u8 Local_au8Password[4];
	u8 Local_u8Flag = 0;
	u8 Local_u8ReadPassword = KPD_NO_PRESSED_KEY;
	u8 Local_u8Tries = Max_Tries;
	u8 i;

	/* initialize DIO pins */
	DIO_voidInit();

	/* Initialize Character LCD */
	CLCD_voidInit();

	/* Initialize Keypad */
	KPD_voidInit();

	/* Initialize DC Motor*/
	DCM_voidInit();

	/* Control the position (0,0) of the printed characters */
	CLCD_voidGoToXY(0,0);

	if(EEPROM_u8ReadeData(EEPROM_Status_Flag)==First_Use) // to check if its the first time to use the safe
	{
		CLCD_voidSendString("Set Password:");
		for( i=0; i<=3 ; i++)
		{
			do
			{
				Local_u8ReadPassword = KPD_u8GetPressedKey();

			} while (Local_u8ReadPassword == KPD_NO_PRESSED_KEY);

			CLCD_voidGoToXY(1,i);
			CLCD_voidSendData(Local_u8ReadPassword);
			_delay_ms(500);
			CLCD_voidGoToXY(1,i);
			CLCD_voidSendData('*');
			EEPROM_enuWriteData(EEPROM_PASSWORD_LOCATION1+i,Local_u8ReadPassword);
		}

		EEPROM_enuWriteData(EEPROM_Status_Flag,Entered_The_Home); // set the flag to 0
	}


	/* Clear LCD */
	CLCD_voidClearScreen();

	/* Control the position (0,2) of the printed characters */
	CLCD_voidGoToXY(0,2);

	/* Print string in LCD */
	CLCD_voidSendString("Welcome To Home");

	/* wait 1000 ms */
	_delay_ms(1000);

	for(;;)
	{
		while(Local_u8Flag == 0)
		{
			/* Clear LCD */
			CLCD_voidClearScreen();

			/* Control the position (0,2) and print string in LCD  */
			CLCD_voidGoToXY(0,2);
			CLCD_voidSendString("Chose a Mode");


			/* wait 1000 ms */
			_delay_ms(100);

			/* Clear LCD */
			CLCD_voidClearScreen();

			Local_u8ReadPassword = KPD_NO_PRESSED_KEY;
			CLCD_voidSendString("1-Enter Pass");
			CLCD_voidGoToXY(1,0);
			CLCD_voidSendString("2-Change Pass");
			do
			{
				Local_u8ReadPassword = KPD_u8GetPressedKey();

			} while (Local_u8ReadPassword == KPD_NO_PRESSED_KEY);
			_delay_ms(500);
			if(Local_u8ReadPassword == '1')
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString("Enter Password:");
				for( i =0 ; i<=3 ; i++)
				{
					do
					{
						CLCD_voidGoToXY(1,i);

						/* Turn on LCD cursor */
						CLCD_voidSendCommand(LCD_CURSOR_ON);

						/* wait 100 ms */
						_delay_ms(100);

						/* Turn off LCD cursor */
						CLCD_voidSendCommand(LCD_CURSOR_OFF);

						Local_au8Password[i] = KPD_u8GetPressedKey();
					} while (Local_au8Password[i]==KPD_NO_PRESSED_KEY);

					CLCD_voidGoToXY(1,i);
					CLCD_voidSendData(Local_au8Password[i]);
					_delay_ms(500);
					CLCD_voidGoToXY(1,i);
					CLCD_voidSendData('*');
				}

				if((EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION1)==Local_au8Password[0]) &&  (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION2)==Local_au8Password[1]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION3)==Local_au8Password[2]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION4)==Local_au8Password[3]) )
				{
					CLCD_voidClearScreen();
					CLCD_voidGoToXY(0,2);
					CLCD_voidSendString("Welcome Back");

					/* Turn on the indicator green led */
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_LOW);

					/* Open the door */
					DCM_voidRotate(CW_STATE);
					_delay_ms(1000);

					/* Stop Motor */
					DCM_voidRotate(STOP_STATE);

					/* The door will open for 4 seconds */
					_delay_ms(4000);

					/* Close the door */
					DCM_voidRotate(CWW_STATE);
					_delay_ms(1000);

					/* Stop Motor */
					DCM_voidRotate(STOP_STATE);

					/* Turn on the indicator red led */
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN0,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_HIGH);

					/* Clear LCD */
					CLCD_voidClearScreen();
					Local_u8Flag=0;

				}
				else if((EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION1)==Local_au8Password[3]) &&  (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION2)==Local_au8Password[2]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION3)==Local_au8Password[1]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION4)==Local_au8Password[0]) )
				{
					CLCD_voidClearScreen();
					CLCD_voidGoToXY(0,1);
					CLCD_voidSendString("Calling Police");

					/* Turn on the indicator blue led */
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_LOW);
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_HIGH);

					/* wait 5000 ms */
					_delay_ms(5000);

					/* Turn on the indicator red led */
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN1,DIO_u8PIN_HIGH);
					DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN2,DIO_u8PIN_LOW);

					/* Clear LCD */
					CLCD_voidClearScreen();

					Local_u8Flag=0;
				}
				else
				{
					Local_u8Tries--;
					/* Check if the three tries are */
					if(Local_u8Tries>0)
					{
						CLCD_voidClearScreen();
						CLCD_voidGoToXY(0,1);
						CLCD_voidSendString("Wrong Password");
						_delay_ms(1000);
						CLCD_voidClearScreen();
						CLCD_voidSendString("Tries Left:");
						CLCD_voidSendData(Local_u8Tries+48);
						_delay_ms(1000);
					}
					else
					{
						/* wait 500 ms */
						_delay_ms(500);

						/* Clear LCD */
						CLCD_voidClearScreen();

						/* Control the position (0,1) and print string in LCD  */
						CLCD_voidGoToXY(0,2);
						CLCD_voidSendString("LOGIN BLOCKED");

						/* Turn on buzzer */
						DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_HIGH);

						_delay_ms(10000);

						/* Turn off buzzer */
						DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_LOW);
						Local_u8Tries = 3;
						Local_u8Flag=0;

						/* exit the for loop and start from super loop */
						continue;
					}
				}
			}
			else if(Local_u8ReadPassword == '2')
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString("Old Password:");
				for( i =0 ; i<=3 ; i++)
				{
					do
					{
						CLCD_voidGoToXY(1,i);
						/* Turn on LCD cursor */
						CLCD_voidSendCommand(LCD_CURSOR_ON);

						/* wait 100 ms */
						_delay_ms(100);

						/* Turn off LCD cursor */
						CLCD_voidSendCommand(LCD_CURSOR_OFF);

						Local_au8Password[i] = KPD_u8GetPressedKey();
					} while (Local_au8Password[i]==KPD_NO_PRESSED_KEY);

					CLCD_voidGoToXY(1,i);
					CLCD_voidSendData(Local_au8Password[i]);
					_delay_ms(500);
					CLCD_voidGoToXY(1,i);
					CLCD_voidSendData('*');
				}


				if((EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION1)==Local_au8Password[0]) &&  (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION2)==Local_au8Password[1]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION3)==Local_au8Password[2]) && (EEPROM_u8ReadeData(EEPROM_PASSWORD_LOCATION4)==Local_au8Password[3]) )
				{
					CLCD_voidClearScreen();
					/* Print string in LCD */
					CLCD_voidSendString("New Pass : ");

					/* Control the position (1,0) and print string in LCD  */
					CLCD_voidGoToXY(1,0);
					CLCD_voidSendString("Just Numbers");

					for( i =0; i<=3 ; i++)
					{

						do
						{
							Local_u8ReadPassword = KPD_u8GetPressedKey();

						} while (Local_u8ReadPassword == KPD_NO_PRESSED_KEY);

						CLCD_voidGoToXY(0,10+i);
						/* Turn on LCD cursor */
						CLCD_voidSendCommand(LCD_CURSOR_ON);

						/* wait 100 ms */
						_delay_ms(100);

						/* Turn off LCD cursor */
						CLCD_voidSendCommand(LCD_CURSOR_OFF);

						CLCD_voidSendData(Local_u8ReadPassword);
						_delay_ms(500);
						CLCD_voidGoToXY(0,10+i);
						CLCD_voidSendData('*');
						EEPROM_enuWriteData(EEPROM_PASSWORD_LOCATION1+i,Local_u8ReadPassword);
					}
				}
				else
				{
					CLCD_voidClearScreen();

					/* Control the position (0,1) and print string in LCD  */
					CLCD_voidGoToXY(0,1);
					CLCD_voidSendString("Wrong Password");

					/* wait 500 ms */
					_delay_ms(500);

					/* Clear LCD */
					CLCD_voidClearScreen();
				}
			}
			else
			{
				CLCD_voidClearScreen();
				CLCD_voidSendString("Invalid Input");
				_delay_ms(1000);
			}
		}
	}
}

