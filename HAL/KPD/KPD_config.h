/**************************************************************************************/
/********************			Author: Ahmed Mohamed			***********************/
/********************			Layer: HAL			 			***********************/
/********************			Component: Keypad  			    ***********************/
/********************			Version: 1.00		 			***********************/
/********************			Date: 16-12-2022	 			***********************/
/**************************************************************************************/


/* Preprocessor file guard */
#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_



//	Keypad port Configuration
#define KEYPAD_PORT_DIR		DDRA
#define KEYPAD_PORT_OUT		PORTA
#define KEYPAD_PORT_IN		PINA

//	Keypad Configuration for Rows & ColumnS
#define	N_ROW 4
#define N_COL 4

// Macros for the keypad size
#define ROW_NUM 4
#define COLUMN_NUM 4

// Macros for the keypad keys
/*#define KPD_ARR_VAL         \
{                           \
    {'1', '2', '3', 'A'},   \
    {'4', '5', '6', 'B'},   \
    {'7', '8', '9', 'C'},   \
    {'*', '0', '#', 'D'}    \
                            \
}*/

// Keypad Port
#define KPD_PORT				DIO_u8PORTA

// The the COLUMN pins -Output-
#define KPD_COLUMN0_PIN			DIO_u8PIN0
#define KPD_COLUMN1_PIN			DIO_u8PIN1
#define KPD_COLUMN2_PIN			DIO_u8PIN2
#define KPD_COLUMN3_PIN			DIO_u8PIN3

// The the ROW pins -Input-
#define KPD_ROW0_PIN			DIO_u8PIN4
#define KPD_ROW1_PIN			DIO_u8PIN5
#define KPD_ROW2_PIN			DIO_u8PIN6
#define KPD_ROW3_PIN			DIO_u8PIN7

#endif

