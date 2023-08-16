/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: MCAL			 			***********************/
/********************			Component: EEPROM			    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 26-3-2023	 				***********************/
/**************************************************************************************/

#ifndef EEPROM_REGISTER_H_
#define EEPROM_REGISTER_H_


#define EEDR      (*(volatile u8*)0x3D)  		 // Data Register

#define EECR      (*(volatile u8*)0x3C)  		 // Control Register

#define EEARL     (*(volatile u16*)0x3E)         // Address Register

#endif /* EEPROM_REGISTER_H_ */
