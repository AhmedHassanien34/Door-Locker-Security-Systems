
/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: HAL			 			**************/
/***********		Component: CLCD			 		**************/
/***********		Version: 1.00		 			**************/
/***********		Date: 17-12-2022	 			**************/
/*****************************************************************/

/* Preprocessor file guard */
#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

/* LCD Data bits mode configuration, its value should be 4 or 8*/
#define CLCD_DATA_BITS_MODE  4

#define CLCD_SIZE_OF_ARRAY			10


/* LCD HW Ports and Pins Ids */
#define CLCD_CTRL_PORT               DIO_u8PORTC

#define CLCD_RS_PIN                  DIO_u8PIN4
#define CLCD_RW_PIN                  DIO_u8PIN5
#define CLCD_E_PIN                   DIO_u8PIN6

#define CLCD_DATA_PORT               DIO_u8PORTB

#define CLCD_D4_PIN                 DIO_u8PIN0
#define CLCD_D5_PIN                 DIO_u8PIN1
#define CLCD_D6_PIN                 DIO_u8PIN2
#define CLCD_D7_PIN                 DIO_u8PIN3


/* LCD Commands */

#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

#endif

