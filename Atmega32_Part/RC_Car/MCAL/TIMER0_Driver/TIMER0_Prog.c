/*
 * TIMER_Prog.c
 *
 *  Created on: ٢٣‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER0_Init.h"
#include "TIMER0_Confg.h"
#include "TIMER0_Priv.h"




void TIMER0_vidInit()
{
#if(TIMER0_MODE == NORMAL_MODE0 )
	CLR_BIT(TCCR0_REG,3);
	CLR_BIT(TCCR0_REG,6);

#elif(TIMER0_MODE == PHASCORCT_MODE0 )
	CLR_BIT(TCCR0_REG,3);
	SET_BIT(TCCR0_REG,6);

#elif(TIMER0_MODE == COMPARE_MODE0 )
	SET_BIT(TCCR0_REG,3);
	CLR_BIT(TCCR0_REG,6);

#elif(TIMER0_MODE == FASTPWM_MODE0 )
	SET_BIT(TCCR0_REG,3);
	SET_BIT(TCCR0_REG,6);
#endif
}


void TIMER0_vidStartTimer_OverFlowMode(u8 u8InitVal)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetInitReg(u8InitVal);

/**********************************************/
/**************Enable Interrupt ***************/
/**********************************************/
SET_BIT(SR_REG,7);  	//Global Interrupt
SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0

/**********************************************/
/******* Start Timing (CLOCK_SELECT)***********/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#endif
}



void TIMER0_vidStartTimer_CTCMode(u8 u8InitVal , u8 u8CompareValue,u8 u8CTCMode)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetInitReg(u8InitVal);

/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetComparReg(u8CompareValue);

/**********************************************/
/**************Enable Interrupt ***************/
/**********************************************/

switch(u8CTCMode)
{
case (TIMER0_CTC_CM_INTRUPT):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0
	CLR_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Disable The Pin Mode
	break;

case (TIMER0_CTC_PINS_TOGGLE):
	CLR_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//Toggle The Pin(OC0) on compare match
	break;

case (TIMER0_CTC_PINS_CLEAR):
	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear The Pin(OC0) on compare match
	break;

case (TIMER0_CTC_PINS_SET):
	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//SET The Pin(OC0) on compare match
	break;

case (TIMER0_CTC_CM_INTRUPT_PINS_TOGGLE):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	CLR_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//Toggle The Pin(OC0) on compare match
	break;

case (TIMER0_CTC_CM_INTRUPT_PINS_CLEAR):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear The Pin(OC0) on compare match
	break;

case (TIMER0_CTC_CM_INTRUPT_PINS_SET):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//SET The Pin(OC0) on compare match
	break;
}

/**********************************************/
/************** Start Timing ******************/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#endif
}




void TIMER0_vidStartTimer_PWMMode(u8 u8InitVal , u8 u8CompareValue,u8 u8PWMMode)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetInitReg(u8InitVal);

/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetComparReg(u8CompareValue);

/**********************************************/
/**************Enable Interrupt ***************/
/**********************************************/

switch(u8PWMMode)
{
case (TIMER0_PWM_OF_CM_INTRUPTS_ONLY):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0
	SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0

	CLR_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Disable The Pin Mode
	break;

case (TIMER0_PWM_PIN_CLEAR_SET):
	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear OC0 on compare match & Set OC0 onThe TOP.
	break;

case (TIMER0_PWM_PIN_SET_CLEAR):
	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//SET OC0 on compare match & CLEAR OC0 onThe TOP.
	break;

case (TIMER0_PWM_OF_INTRUPT_PIN_CLEAR_SET):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear OC0 on compare match & Set OC0 onThe TOP.
	break;

case (TIMER0_PWM_OF_INTRUPT_PIN_SET_CLEAR):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//SET OC0 on compare match & CLEAR OC0 onThe TOP.
	break;

case (TIMER0_PWM_CM_INTRUPT_PIN_CLEAR_SET):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear OC0 on compare match & Set OC0 onThe TOP.
	break;

case (TIMER0_PWM_CM_INTRUPT_PIN_SET_CLEAR):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//SET OC0 on compare match & CLEAR OC0 onThe TOP.
	break;

case (TIMER0_PWM_OF_CM_INTRUPT_PIN_SET_CLEAR):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//SET OC0 on compare match & CLEAR OC0 onThe TOP.
	break;

case (TIMER0_PWM_OF_CM_INTRUPT_PIN_CLEAR_SET):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0

	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear OC0 on compare match & Set OC0 onThe TOP.
	break;
}

/**********************************************/
/************** Start Timing ******************/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#endif
}


void TIMER0_vidStartTimer_PhaseCorrectMode(u8 u8InitVal , u8 u8CompareValue,u8 u8PhsCrrectMode)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetInitReg(u8InitVal);

/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER0_vidSetComparReg(u8CompareValue);

switch(u8PhsCrrectMode)
{
case (TIMER0_PHASECORRECT_PIN_CLEAR_SET):
	SET_BIT(TCCR0_REG,5);CLR_BIT(TCCR0_REG,4);	//Clear The Pin At Up And Set At Down
	break;

case (TIMER0_PHASECORRECT_PIN_SET_CLEAR):
	SET_BIT(TCCR0_REG,5);SET_BIT(TCCR0_REG,4);	//Set The Pin At Up And Clear At Down
	break;
}

/**********************************************/
/************** Start Timing ******************/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR0_REG,2);
	SET_BIT(TCCR0_REG,1);
	SET_BIT(TCCR0_REG,0);

#endif
}


void TIMER0_vidSetInitReg(u8 u8InitVal)
{
	 TCNT0_REG = u8InitVal;
}

void TIMER0_vidSetComparReg(u8 u8CompareValue)
{
	 OCR0_REG = u8CompareValue;
}


u8 TIMER0_vidGetCounterReg(void)
{
	return (TCNT0_REG) ;
}

u8 TIMER0_vidGETComparReg(void)
{
	return (OCR0_REG);
}

void TIMER0_vidEnableOverFlowInterrupt(void)
{
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0
}
void TIMER0_vidEnableCompareMatchInterrupt(void)
{
	SET_BIT(SR_REG,7);  	//Global Interrupt
	SET_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0
}

void TIMER0_vidDisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK_REG,0);	//Over Flow Interrupt For Timer 0
}
void TIMER0_vidDisableCompareMatchInterrupt(void)
{
	CLR_BIT(TIMSK_REG,1);	//Output Compare Interrupt For Timer 0
}

void TIMER0_vidStopTimer(void)
{
	CLR_BIT(TCCR0_REG,2);
	CLR_BIT(TCCR0_REG,1);
	CLR_BIT(TCCR0_REG,0);
}

void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	Timer0_OF_Call_Back();
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	Timer0_CTC_Call_Back();
}

