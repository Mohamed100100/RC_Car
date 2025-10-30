/*
 * DIO_Priv.h
 *
 *  Created on: ١١‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

/*Here we will define all macros are variable or macros that
 * we don't need the user to use it*/

#ifndef DIO_PRIV_H_
#define DIO_PRIV_H_

/*ALL Ports i will need them through the operations*/

/*PORT A Register Definition*/
#define PORTA_REG (*(volatile u8*)0x3B)
#define PINA_REG  (*(volatile u8*)0x39)
#define DDRA_REG  (*(volatile u8*)0x3A)

/*PORT B Register Definition*/
#define PORTB_REG (*(volatile u8*)0x38)
#define PINB_REG  (*(volatile u8*)0x36)
#define DDRB_REG  (*(volatile u8*)0x37)

/*PORT C Register Definition*/
#define PORTC_REG (*(volatile u8*)0x35)
#define PINC_REG  (*(volatile u8*)0x33)
#define DDRC_REG  (*(volatile u8*)0x34)

/*PORT D Register Definition*/
#define PORTD_REG (*(volatile u8*)0x32)
#define PIND_REG  (*(volatile u8*)0x30)
#define DDRD_REG  (*(volatile u8*)0x31)

/*DIO Interrupts Register Definition*/

/* This Register Has The Statues Of The INT0,1
 * Bit3		Bit2	Bit1	Bit0
 * ISC11	ISC10	ISC01	ISC00*/
#define MCUCR_REG	 (*(volatile u8*)0x55)
/***************************************************/

/* This Register Has The Statues Of The INT2
 * Bit6
 * ISC2 */
#define MCUCSR_REG	 (*(volatile u8*)0x54)
/***************************************************/

/* This Register Has The Enable Of The INT0,1,2
 * Bit7		Bit6	Bit5
 * INT1		INT0	INT2*/
#define GICR_REG 	 (*(volatile u8*)0x5B)
/***************************************************/

/* This Register Has The Flag Of The INT0,1,2 (We Almost don't use it)
 * Bit7		Bit6	Bit5
 * INT1		INT0	INT2*/
#define GIFR_REG 	 (*(volatile u8*)0x5A)
/***************************************************/

/* This Register Has The Enable Of All Interrupts
 * Bit7
 * I		*/
#define  SR_REG 	 (*(volatile u8*)0x5F)
/***************************************************/

#endif /* DIO_PRIV_H_ */
