/*
 * TIMER_Priv.h
 *
 *  Created on: ٢٣‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#ifndef TIMER0_PRIV_H_
#define TIMER0_PRIV_H_

/* This Macros For Modes Of Timer */
#define NORMAL_MODE0		0
#define PHASCORCT_MODE0		1
#define COMPARE_MODE0		2
#define FASTPWM_MODE0		3
/*********************************************/
#define NO_CLK_OFF           0
#define CLK_NO_PRESCALER     1
#define CLK_8_PRESCALER      2
#define CLK_64_PRESCALER     3
#define CLK_256_PRESCALER    4
#define CLK_1024_PRESCALER   5
#define EXT_CLK_F_EDGE       6
#define EXT_CLK_R_EDGE       7
/*********************************************/

/* This Register Control The Timer0
 * Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
 * FOC0 	WGM00 	COM01 	COM00 	WGM01 	CS02 	CS01 	CS00
 ******************************************************************
 * FOC0        	  >> Force Output Compare
 * WGM00,WGM01    >> Waveform Generation Mode
 * COM01,COM00    >> Control The OC0 Pin In Each Mode(Don' Work At Normal Mode)
 * CS02,CS01,CS00 >> Control The Clock Selected
 * *****************************************************************/
#define TCCR0_REG	 (*(volatile u8*)0x53)
/*******************************************************************/

/* This Register Has The Initial Value Of Counting At The Timer0*/
#define TCNT0_REG	 (*(volatile u8*)0x52)
/*******************************************************************/

/* This Register Has The Value compared with the counter value  At The Timer0*/
#define OCR0_REG	 (*(volatile u8*)0x5C)
/*******************************************************************/

/* This Register Control The Timer0(Interrupts Enables)
 * Bit1		Bit0
 * OCIE0 	TOIE0
 ******************************************************************
 * OCIE0 >> Timer/Counter0 Output Compare Match Interrupt Enable
 * TOIE0 >> Timer/Counter0 Overflow Interrupt Enable
 * *****************************************************************/
#define TIMSK_REG	 (*(volatile u8*)0x59)
/*******************************************************************/

/* This Register Control The Timer0(Interrupts Flags)
 * Bit1		Bit0
 * OCF0 	TOV0
 ******************************************************************
 * OCF0 >> Output Compare Flag 0
 * TOV0 >> Timer/Counter0 Overflow Flag
 * *****************************************************************/
#define TIFR_REG	 (*(volatile u8*)0x58)
/*******************************************************************/


/* This Register Has The Enable Of All Interrupts
 * Bit7
 * I		*/
#define  SR_REG 	 (*(volatile u8*)0x5F)
/***************************************************/

/* This Register Has The Reset Of The PreScaller
 * Bit0
 * PSR10		*/
#define  SFIOR_REG 	 (*(volatile u8*)0x50)
/***************************************************/




#endif /* TIMER0_PRIV_H_ */
