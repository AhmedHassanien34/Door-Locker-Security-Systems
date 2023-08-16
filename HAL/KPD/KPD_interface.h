/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: HAL			 			***********************/
/********************			Component: Keypad  			    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 16-12-2022	 			***********************/
/**************************************************************************************/

/* Preprocessor file guard */
#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

/* Private Macros for if the button is pressed or not */
#define KPD_PRESSED_KEY 		0x00
#define KPD_NO_PRESSED_KEY 		0xff

void KPD_voidInit(void);

u8 KPD_u8GetPressedKey(void);

#endif
