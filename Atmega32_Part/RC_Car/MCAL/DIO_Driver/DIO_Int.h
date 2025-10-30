/*
 * DIO_Int.h
 *
 *  Created on: ١١‏/٠٩‏/٢٠٢٣
 *      Author: Eng.Mohamed Gamal
 */

#ifndef DIO_INT_H_
#define DIO_INT_H_

/*This macros are responsible on the argument u8PortId
 * it has 4 cases (1)PORTA -(2)PORTB -(3)PORTC -(4)PORTD  */
#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

/*This macros are responsible on the argument u8PinId
 * it has 8 cases (1)PIN0 -(2)PIN1 -(3)PIN2 -(4)PIN3 and so on  */
#define DIO_PIN0 0
#define DIO_PIN1 1
#define DIO_PIN2 2
#define DIO_PIN3 3
#define DIO_PIN4 4
#define DIO_PIN5 5
#define DIO_PIN6 6
#define DIO_PIN7 7

/*This macros are responsible on the argument u8PinDir
 * it has 2 cases (1)Input -(2)Output */
/*This macros are responsible on the argument u8PortDir
 * it has 3 cases (1)All Input -(2)All Output -(3)Masked Value */
#define DIO_INPUT  0x00
#define DIO_OUTPUT 0xff

/*This macros are responsible on the argument u8PinVal
 * it has 2 cases (1)High -(2)Low */
/*This macros are responsible on the argument u8PortVal
 * it has 2 cases (1)All High -(2)All Low -(3)Masked Value */
#define DIO_LOW  0x00
#define DIO_HIGH 0xff

#define DIO_UNDEFINED_VALUE 0xff


/*This macros are responsible on the argument u8InterNum
 * it has 3 cases (1)INT_NUM0 -(2)INT_NUM1 -(3)INT_NUM2 */
#define DIO_INT_NUM0	0
#define DIO_INT_NUM1	1
#define DIO_INT_NUM2	2

/*This macros are responsible on the argument u8InterStat
 * it has 4 cases (1)INT_LOW_LEVEL -(2)INT_R_F_EDGE -(3)INT_F_EDGE -(4)INT_R_EDGE */
#define DIO_INT_LOW_LEVEL		0
#define DIO_INT_R_F_EDGE		1
#define DIO_INT_F_EDGE			2
#define DIO_INT_R_EDGE			3


/*****************CALLBACK FUNCTIONS**********************/
void (*EXT_INT0_Call_Back)(void)  ;

void (*EXT_INT1_Call_Back)(void) ;

void (*EXT_INT2_Call_Back)(void) ;


/**********************************************************/


void DIO_vidSetPinDir(u8 u8PortId , u8 u8PinId , u8 u8PinDir);

void DIO_vidSetPinVal(u8 u8PortId , u8 u8PinId , u8 u8PinVal);

void DIO_vidTogglePinVal(u8 u8PortId , u8 u8PinId);

void DIO_vidEnablePullUpRes(u8 u8PortId , u8 u8PinId);

u8 DIO_u8GetPinVal(u8 u8PortId , u8 u8PinId);

u8 DIO_u8GetPortVal(u8 u8PortId);

void DIO_vidSetPortDir(u8 u8PortId , u8 u8PortDir);

void DIO_vidSetPortVal(u8 u8PortId , u8 u8PortVal);

void DIO_vidEnableIntrupt(u8 u8InterNum,u8 u8InterStat);

void DIO_vidDisableExtInt(u8 u8InterNum);


#endif /* DIO_INT_H_ */
