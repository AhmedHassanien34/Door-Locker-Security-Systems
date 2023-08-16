/*****************************************************************/
/***********		Author: Ahmed Mohamed 			**************/
/***********		Layer: HAL			 			**************/
/***********		Component: DC_Motor		 		**************/
/***********		Version: 1.00		 			**************/
/***********		Date: 17-12-2022	 			**************/
/*****************************************************************/


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_

#define CW_STATE			1
#define CWW_STATE			2
#define STOP_STATE			3

void DCM_voidInit(void);

void DCM_voidCW(void);

void DCM_voidCCW(void);

void DCM_voidRotate(u8 Local_u8State );



#endif
