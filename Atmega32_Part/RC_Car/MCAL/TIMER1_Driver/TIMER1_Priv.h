/*
 * TIMER_Priv.h
 *
 *  Created on: ٢٣‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#ifndef TIMER1_PRIV_H_
#define TIMER1_PRIV_H_

/* This Macros For Modes Of Timer */
#define MODE_01	      0
#define MODE_02	      1
#define MODE_03	      2
#define MODE_04	      3
#define MODE_05       4
#define MODE_06       5
#define MODE_07       6
#define MODE_08       7
#define MODE_09       8
#define MODE_10       9
#define MODE_11       10
#define MODE_12       11
#define MODE_13       12
#define MODE_14       13
#define MODE_15       14
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

/* This Register Control The Timer1
 * Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
 * COM1A1 	COM1A0 	COM1B1 	COM1B0 	FOC1A 	FOC1B 	WGM11 	WGM10
 ******************************************************************
 * COM1A1,COM1A0  >> Control The OC1A Pin In Each Mode(Don' Work At Normal Mode)
 * COM1B1,COM1B0  >> Control The OC1B Pin In Each Mode(Don' Work At Normal Mode)
 * FOC1A	      >> Force Output Compare for Channel A
 * FOC1B	      >> Force Output Compare for Channel B
 * WGM11,WGM10    >>  Waveform Generation Mode
 * *****************************************************************/
#define TCCR1A_REG	 (*(volatile u8*)0x4F)
/*******************************************************************/

/* This Register Control The Timer1
 * Bit7		Bit6	Bit5	Bit4	Bit3	Bit2	Bit1	Bit0
 * ICNC1 	ICES1 	---		WGM13 	WGM12 	CS12 	CS11 	CS10
 ******************************************************************
 * ICNC1 		  >> Input Capture Noise Canceler
 * ICES1  		  >> Input Capture Edge Select
 * WGM13,WGM12    >> Waveform Generation Mode(in addition to WGM11,WGM10)
 * CS12,CS11,CS10 >> Clock Select
 * *****************************************************************/
#define TCCR1B_REG	 (*(volatile u8*)0x4E)
/*******************************************************************/


/* This Register Has The Initial Value Of Counting At The Timer1(High)*/
#define TCNT1H_REG	 (*(volatile u8*)0x4D)
/*******************************************************************/

/* This Register Has The Initial Value Of Counting At The Timer1(Low)*/
#define TCNT1L_REG	 (*(volatile u8*)0x4C)
/*******************************************************************/

/* This Register Has The Value compared with the counter value  At The Timer1(High)
 * Channel A*/
#define OCR1AH_REG	 (*(volatile u8*)0x4B)
/*******************************************************************/

/* This Register Has The Value compared with the counter value  At The Timer1(Low)
 * Channel A*/
#define OCR1AL_REG	 (*(volatile u8*)0x4A)
/*******************************************************************/

/* This Register Has The Value compared with the counter value  At The Timer1(High)
 * Channel B*/
#define OCR1BH_REG	 (*(volatile u8*)0x49)
/*******************************************************************/

/* This Register Has The Value compared with the counter value  At The Timer1(Low)
 * Channel B*/
#define OCR1BL_REG	 (*(volatile u8*)0x48)
/*******************************************************************/


/* This Register Has The Value Input Capture At The Timer1(High)*/
#define ICR1H_REG	 (*(volatile u8*)0x47)
/*******************************************************************/

/* This Register Has The Value Input Capture At The Timer1(Low)*/
#define ICR1L_REG	 (*(volatile u8*)0x46)
/*******************************************************************/



/* This Register Control The Timer1(Interrupts Enables)
 * Bit5		Bit4	Bit3	Bit2
 * TICIE1 	OCIE1A 	OCIE1B 	TOIE
 ******************************************************************
 * TICIE1 >> Timer/Counter1, Input Capture Interrupt Enable
 * OCIE1A >> Timer/Counter1, Output Compare A Match Interrupt Enable
 * OCIE1B >> Timer/Counter1, Output Compare B Match Interrupt Enable
 * TOIE   >> Timer/Counter1, Overflow Interrupt Enable
 * *****************************************************************/
#define TIMSK_REG	 (*(volatile u8*)0x59)
/*******************************************************************/

/* This Register Control The Timer0(Interrupts Flags)
 * Bit5		Bit4	Bit3	Bit2
 * ICF1 	OCF1A 	OCF1B 	TOV1
 ******************************************************************
 * ICF1  >> Timer/Counter1, Input Capture Flag
 * OCF1A >> Timer/Counter1, Output Compare A Match Flag
 * OCF1B >> Timer/Counter1, Output Compare B Match Flag
 * TOV1  >> Timer/Counter1, Overflow Flag
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




#endif /* TIMER1_PRIV_H_ */
