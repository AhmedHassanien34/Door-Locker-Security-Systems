/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: MCAL			 			***********************/
/********************			Component: EEPROM			    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 26-3-2023	 				***********************/
/**************************************************************************************/

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

// Check Error Status
typedef enum
{
 	EEPROM_OK,
	 EEPROM_NOK
}EEPROM_tenuErrorStatus;

EEPROM_tenuErrorStatus EEPROM_enuWriteData(u16 Copy_u16Address , u8 Copy_u8Data);

u8 EEPROM_u8ReadeData(u16 Copy_u16Address);

#endif /* EEPROM_INTERFACE_H_ */
