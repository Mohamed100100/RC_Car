/*
 * TIMER_Init.h
 *
 *  Created on: ٢٣‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#ifndef TIMER0_INIT_H_
#define TIMER0_INIT_H_

/*
 * OF >> Over Flow
 * CM >> Compare Match
 * Set_Clear(NoN Inverted)
 * 		  -----------
 * 		  |			|
 * -------|			|-------
 * 		 CM			OF
 ************************************
 * Clear_Set(Inverted)
 * ----------		-------
 *   		|		|
 * 			|-------|
 * 		 	CM		OF
 */

/*This Macros For u8CTCMode Argument*/
#define TIMER0_CTC_CM_INTRUPT			0

#define TIMER0_CTC_PINS_TOGGLE			1
#define TIMER0_CTC_PINS_CLEAR			2
#define TIMER0_CTC_PINS_SET				3

#define TIMER0_CTC_CM_INTRUPT_PINS_TOGGLE	4
#define TIMER0_CTC_CM_INTRUPT_PINS_CLEAR	5
#define TIMER0_CTC_CM_INTRUPT_PINS_SET		6
/**********************************************************/

/* This Macros For u8PWMMode Argument */
#define TIMER0_PWM_OF_CM_INTRUPTS_ONLY			0

#define TIMER0_PWM_PIN_CLEAR_SET				1
#define TIMER0_PWM_PIN_SET_CLEAR				2

#define TIMER0_PWM_OF_INTRUPT_PIN_CLEAR_SET		3
#define TIMER0_PWM_OF_INTRUPT_PIN_SET_CLEAR		4

#define TIMER0_PWM_CM_INTRUPT_PIN_CLEAR_SET		5
#define TIMER0_PWM_CM_INTRUPT_PIN_SET_CLEAR		6

#define TIMER0_PWM_OF_CM_INTRUPT_PIN_SET_CLEAR	7
#define TIMER0_PWM_OF_CM_INTRUPT_PIN_CLEAR_SET	8
/**********************************************************/


/*This Macros For u8PhsCrrectMode Argument*/
#define TIMER0_PHASECORRECT_PIN_CLEAR_SET				1
#define TIMER0_PHASECORRECT_PIN_SET_CLEAR				2
/**********************************************************/


/*****************CALLBACK FUNCTIONS**********************/
void (*Timer0_OF_Call_Back)(void)  ;

void (*Timer0_CTC_Call_Back)(void) ;

/*********************************************************/

/*This Function Must Be Called At The First To Set The Mode (In Confg File)*/
void TIMER0_vidInit();


/*This Function Can Be Called Only When You Are Normal Mode*/
/***** You Have At This Mode One Feature*********************/
/***** (1) Over Flow Interrupt Only**************************/
void TIMER0_vidStartTimer_OverFlowMode(u8 u8InitVal);



/*This Function Can Be Called Only When You Are CTC Mode*/
/***** You Have At This Mode Three Feature*******************/
/***** (1) Compare Match Interrupt **************************/
/***** (2) Display OC0 Pin **********************************/
/***** (3) Both Interrupt And Pin OC0 ***********************/
void TIMER0_vidStartTimer_CTCMode(u8 u8InitVal , u8 u8CompareValue,u8 u8CTCMode);



/*This Function Can Be Called Only When You Are PWM Mode*/
/***** You Have At This Mode five Feature********************/
/***** (1) Both Over Flow And Compare Match Interrupts ******/
/***** (2) Display OC0 Pin **********************************/
/***** (3) Pin OC0 And Over Flow Interrupt ******************/
/***** (4) Pin OC0 And Compare Match Interrupt **************/
/***** (5) Pin OC0 And Both Interrupts **********************/
void TIMER0_vidStartTimer_PWMMode(u8 u8InitVal , u8 u8CompareValue,u8 u8PWMMode);



/*This Function Can Be Called Only When You Are Phase Correct Mode*/
/***** You Have At This Mode Three Feature*******************/
/***** (1) Display OC0 Pin (Clear The Set) ******************/
/***** (2) Display OC0 Pin (Set The Clear)*******************/
void TIMER0_vidStartTimer_PhaseCorrectMode(u8 u8InitVal , u8 u8CompareValue,u8 u8PhsCrrectMode);



/*This Function You May Need Them (Helper)*/
void TIMER0_vidSetInitReg(u8 u8InitVal);

void TIMER0_vidSetComparReg(u8 u8CompareValue);

u8 TIMER0_vidGetCounterReg(void);

u8 TIMER0_vidGetCounterReg(void);

u8 TIMER0_vidGETComparReg(void);

void TIMER0_vidEnableOverFlowInterrupt(void);

void TIMER0_vidEnableCompareMatchInterrupt(void);

void TIMER0_vidDisableOverFlowInterrupt(void);

void TIMER0_vidDisableCompareMatchInterrupt(void);


void TIMER0_vidStopTimer(void);



/*TIMER0 In OverFlowMode*/

#endif /* TIMER0_INIT_H_ */
