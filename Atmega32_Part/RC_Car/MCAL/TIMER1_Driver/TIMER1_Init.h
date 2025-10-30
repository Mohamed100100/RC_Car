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
 * IC >> Input Capture
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
#define TIMER1_CTC_CM_INTRUPT			0

#define TIMER1_CTC_PINS_TOGGLE			1
#define TIMER1_CTC_PINS_CLEAR			2
#define TIMER1_CTC_PINS_SET				3

#define TIMER1_CTC_CM_INTRUPT_PINS_TOGGLE	4
#define TIMER1_CTC_CM_INTRUPT_PINS_CLEAR	5
#define TIMER1_CTC_CM_INTRUPT_PINS_SET		6
/**********************************************************/

/* This Macros For u8PWMMode Argument */

#define TIMER1_PWM_PIN_CLEAR_SET				1
#define TIMER1_PWM_PIN_SET_CLEAR				2
/**********************************************************/

/* This Macros For u8EdgeSel Argument */

#define TIMER1_IC_FALLING				1
#define TIMER1_IC_RAISING				2
/**********************************************************/

/*This Macros For u8PhsCrrectMode Argument*/
#define TIMER1_PHASECORRECT_PIN1A_CLEAR_SET				1
#define TIMER1_PHASECORRECT_PIN1A_SET_CLEAR				2
#define TIMER1_PHASECORRECT_PIN1B_CLEAR_SET				3
#define TIMER1_PHASECORRECT_PIN1B_SET_CLEAR				4
/**********************************************************/

/*This Macros For u8Channel Argument*/
#define TIMER1_CHANNEL_A		1
#define TIMER1_CHANNEL_B		2
/**********************************************************/


/*****************CALLBACK FUNCTIONS**********************/
void (*Timer1_OF_Call_Back)(void)  ;

void (*Timer1_CTC_A_Call_Back)(void) ;

void (*Timer1_CTC_B_Call_Back)(void) ;

void (*Timer1_IC_Call_Back)(void) ;
/*********************************************************/

/*This Function Must Be Called At The First To Set The Mode (In Confg File)*/
void TIMER1_vidInit(void);


/*This Function Can Be Called Only When You Are Normal Mode*/
/***** You Have At This Mode One Feature*********************/
/***** (1) Over Flow Interrupt Only**************************/
void TIMER1_vidStartTimer_OverFlowMode(u16 u16InitVal);



/*This Function Can Be Called Only When You Are CTC Mode*/
/***** You Have At This Mode Three Feature*******************/
/***** (1) Compare Match Interrupt **************************/
/***** (2) Display OC1A Pin *********************************/
/***** (2) Display OC1B Pin *********************************/
/***** (3) Both Interrupt And Pin OC1A ***********************/
void TIMER1_vidStartTimer_CTCMode(u16 u8InitVal , u16 u16CompareValue,u8 u8CTCMode,u8 u8Channel);



/*This Function Can Be Called Only When You Are PWM Mode*/
/***** You Have At This Mode More Than One Feature ***********/
/***** (1) Display OC1A Pin **********************************/
/***** (2) Display Pin OC1B **********************************/
/*>>NOTE<< If You Want To Enable Any Interrupt Go To The Helper Functions And Choose From it*/
void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel);



/*This Function Can Be Called Only When You Are Phase Correct*/
/***** You Have At This Mode Three Feature***********************/
/***** (1) Display OC1A Pin (Clear The Set) *********************/
/***** (2) Display OC1A Pin (Set The Clear)**********************/
/***** (3) Display OC1B Pin (Clear The Set) *********************/
/***** (4) Display OC1B Pin (Set The Clear)**********************/
/* NOTE >>> if You Want To Make The A&B Call This Function Twice*/
void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode);


/*This Function Can Be Called Only When You Are Normal Mode*/
/***** You Can Detect By It The PWM At The Pin ICP1(PIND6)********/

/* NOTE >>> If You Want To Know The PWM ,You Need To Know Period
 * And Duty Cycle ,You Can Detect Them By 3 Edges (At ISR Of IC1)*/
void TIMER1_vidDisplayInputCaptureMode(u8 u8EdgeSel);


/*This Function You May Need Them (Helper)*/
void TIMER1_vidSetInitReg(u16 u16InitVal);

void TIMER1_vidSetComparReg_ChannelA(u16 u16CompareValue);

void TIMER1_vidSetComparReg_ChannelB(u16 u16CompareValue);

void TIMER1_vidSetInputCaptureReg(u16 u16InputCapture);

u16 TIMER1_u16GetCounterReg(void);

u16 TIMER1_u16GetComparReg_ChannelA(void);

u16 TIMER1_u16GetComparReg_ChannelB(void);

u16 TIMER1_u16GetInputCaptureReg(void);


void TIMER1_vidEnableOverFlowInterrupt(void);

void TIMER1_vidEnableCompareMatchInterrupt_ChannelA(void);

void TIMER1_vidEnableCompareMatchInterrupt_ChannelB(void);

void TIMER1_vidEnableInputCaptureInterrupt(void);

void TIMER1_vidDisableOverFlowInterrupt(void);

void TIMER1_vidDisableCompareMatchInterrupt_ChannelA(void);

void TIMER1_vidDisableCompareMatchInterrupt_ChannelB(void);

void TIMER1_vidDisableInputCaptureInterrupt(void);

void TIMER1_vidStopTimer(void);



/*TIMER0 In OverFlowMode*/

#endif /* TIMER0_INIT_H_ */
