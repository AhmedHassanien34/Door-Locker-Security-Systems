/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: MCAL			 			***********************/
/********************			Component: EEPROM			    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 26-3-2023	 				***********************/
/**************************************************************************************/

/********************************************************************************************/
/* Include libraries                                                                        */
/********************************************************************************************/
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "EEPROM_register.h"
#include "EEPROM_config.h"
#include "EEPROM_private.h"
#include "EEPROM_interface.h"

EEPROM_tenuErrorStatus EEPROM_enuWriteData(u16 Copy_u16Address , u8 Copy_u8Data)
{
	EEPROM_tenuErrorStatus Local_enuErrorStatus = EEPROM_OK;

	if( Copy_u8Data > 255)
	{
		Local_enuErrorStatus = EEPROM_NOK;
	}
	else
	{

		// Set up Address Register
		EEARL = Copy_u16Address;

		// Set Up Data Register
		EEDR = Copy_u8Data ;

		// Write one to the EEMWE
		EECR |= (1<<2);

		// Start EEPROM Write by Setting EEWE to 1
		EECR |= (1<<1);

		// Polling on the flag (wait for the write operation to be completed )
		while((EECR >> 1 & 1) == 1);
	}
	return Local_enuErrorStatus;
}

u8 EEPROM_u8ReadeData(u16 Copy_u16Address)
{

	// Set up Address Register
	EEARL = Copy_u16Address;

	// Start EEPROM Read by Setting EERE to 1
	EECR |= (1<<0);

	// Reading Operation takes only one cycle so it's not neccessry to polling on the flag
	return EEDR;

}
