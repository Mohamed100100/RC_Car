/*
 * TIMER_Prog.c
 *
 *  Created on: ٢٣‏/٠٩‏/٢٠٢٣
 *      Author: vmk9p-'
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER1_Init.h"
#include "TIMER1_Confg.h"
#include "TIMER1_Priv.h"




void TIMER1_vidInit(void)
{
#if(TIMER1_MODE == MODE_01 )
CLR_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_02 )
CLR_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_03 )
CLR_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_04 )
CLR_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_05 )
CLR_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_06 )
CLR_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_07 )
CLR_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_08 )
CLR_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_09 )
SET_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_10 )
SET_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_11 )
SET_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_12 )
SET_BIT(TCCR1B_REG,4);CLR_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_13 )
SET_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
CLR_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_14 )
SET_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);CLR_BIT(TCCR1A_REG,0);

#elif(TIMER1_MODE == MODE_15 )
SET_BIT(TCCR1B_REG,4);SET_BIT(TCCR1B_REG,3);
SET_BIT(TCCR1A_REG,1);SET_BIT(TCCR1A_REG,0);

#endif
}


void TIMER1_vidStartTimer_OverFlowMode(u16 u16InitVal)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER1_vidSetInitReg(u16InitVal);

/**********************************************/
/**************Enable Interrupt ***************/
/**********************************************/
SET_BIT(SR_REG,7);  	//Global Interrupt
SET_BIT(TIMSK_REG,2);	//Over Flow Interrupt For Timer 1

/**********************************************/
/******* Start Timing (CLOCK_SELECT)***********/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#endif
}



void TIMER1_vidStartTimer_CTCMode(u16 u16InitVal , u16 u16CompareValue,u8 u8CTCMode,u8 u8Channel)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER1_vidSetInitReg(u16InitVal);

/**********************************************/
/**************Set Compared Value **************/
/**********************************************/
#if(TIMER1_MODE == MODE_05)
	TIMER1_vidSetComparReg_ChannelA(u16CompareValue);

#elif(TIMER1_MODE == MODE_13)
	TIMER1_vidSetInputCaptureReg(u16CompareValue);

#endif

/**********************************************/
/**************Enable Interrupt ***************/
/**********************************************/

switch(u8CTCMode)
{
case (TIMER1_CTC_CM_INTRUPT):
	SET_BIT(SR_REG,7);  	//Global Interrupt

	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TIMSK_REG,4);break;//Output Compare Interrupt For Timer 1A
	case (TIMER1_CHANNEL_B):SET_BIT(TIMSK_REG,3);break;//Output Compare Interrupt For Timer 1B
	}
	break;

case (TIMER1_CTC_PINS_TOGGLE):
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):CLR_BIT(TCCR1A_REG,7);SET_BIT(TCCR1A_REG,6);break;
	case (TIMER1_CHANNEL_B):CLR_BIT(TCCR1A_REG,5);SET_BIT(TCCR1A_REG,4);break;
	} //Toggle The Pin1 A or B on compare match
	break;

case (TIMER1_CTC_PINS_CLEAR):
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TCCR1A_REG,7);CLR_BIT(TCCR1A_REG,6);break;
	case (TIMER1_CHANNEL_B):SET_BIT(TCCR1A_REG,5);CLR_BIT(TCCR1A_REG,4);break;
	}	//Clear The Pin1 A or B on compare match
	break;

case (TIMER1_CTC_PINS_SET):
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TCCR1A_REG,7);SET_BIT(TCCR1A_REG,6);break;
	case (TIMER1_CHANNEL_B):SET_BIT(TCCR1A_REG,5);SET_BIT(TCCR1A_REG,4);break;
	}	//SET The Pin1 A or B on compare match
	break;

case (TIMER1_CTC_CM_INTRUPT_PINS_TOGGLE):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):CLR_BIT(TCCR1A_REG,7);SET_BIT(TCCR1A_REG,6);//Toggle The Pin1 A  on compare match
							SET_BIT(TIMSK_REG,4);break;//Output Compare Interrupt For Timer 1A
	case (TIMER1_CHANNEL_B):CLR_BIT(TCCR1A_REG,5);SET_BIT(TCCR1A_REG,4);//Toggle The Pin1 B on compare match
							SET_BIT(TIMSK_REG,3);break;//Output Compare Interrupt For Timer 1B
	}break;

case (TIMER1_CTC_CM_INTRUPT_PINS_CLEAR):
	SET_BIT(SR_REG,7);  	//Global Interrupt
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TCCR1A_REG,7);CLR_BIT(TCCR1A_REG,6);//Clear The Pin1 A on compare match
							SET_BIT(TIMSK_REG,4);break;//Output Compare Interrupt For Timer 1A
	case (TIMER1_CHANNEL_B):SET_BIT(TCCR1A_REG,5);CLR_BIT(TCCR1A_REG,4);//Clear The Pin1 B on compare match
							SET_BIT(TIMSK_REG,3);break;//Output Compare Interrupt For Timer 1B
	}break;

	case (TIMER1_CTC_CM_INTRUPT_PINS_SET):
	SET_BIT(SR_REG,7);  //Global Interrupt
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TCCR1A_REG,7);SET_BIT(TCCR1A_REG,6);//SET The Pin1 A on compare match
							SET_BIT(TIMSK_REG,4);break;//Output Compare Interrupt For Timer 1A
	case (TIMER1_CHANNEL_B):SET_BIT(TCCR1A_REG,5);SET_BIT(TCCR1A_REG,4);//SET The Pin1 B on compare match
							SET_BIT(TIMSK_REG,3);break;//Output Compare Interrupt For Timer 1B
	}break;
}

/**********************************************/
/******* Start Timing (CLOCK_SELECT)***********/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#endif
}




void TIMER1_vidStartTimer_PWMMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PWMMode ,u8 u8Channel)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER1_vidSetInitReg(u16InitVal);

/**********************************************/
/**************Set Compared Value **************/
/**********************************************/
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):TIMER1_vidSetComparReg_ChannelA(u16CompareValue);break;
	case (TIMER1_CHANNEL_B):TIMER1_vidSetComparReg_ChannelB(u16CompareValue);break;
	}
/**********************************************/
/**************Enable Interrupt ***************/
/**********************************************/

switch(u8PWMMode)
{
case (TIMER1_PWM_PIN_CLEAR_SET):
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TCCR1A_REG,7);CLR_BIT(TCCR1A_REG,6);break;
	case (TIMER1_CHANNEL_B):SET_BIT(TCCR1A_REG,5);CLR_BIT(TCCR1A_REG,4);break;
	}//Clear OC1A/OC1B on compare match, set OC1A/OC1B at TOP
	break;

case (TIMER1_PWM_PIN_SET_CLEAR):
	switch(u8Channel)
	{
	case (TIMER1_CHANNEL_A):SET_BIT(TCCR1A_REG,7);SET_BIT(TCCR1A_REG,6);break;
	case (TIMER1_CHANNEL_B):SET_BIT(TCCR1A_REG,5);SET_BIT(TCCR1A_REG,4);break;
	}//Set OC1A/OC1B on compare match, clear OC1A/OC1B at TOP
	break;
}

/**********************************************/
/******* Start Timing (CLOCK_SELECT)***********/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#endif
}


void TIMER1_vidStartTimer_PhaseCorrectMode(u16 u16InitVal , u16 u16CompareValue,u8 u8PhsCrrectMode)
{
/**********************************************/
/**************Set Initial Value **************/
/**********************************************/
	TIMER1_vidSetInitReg(u16InitVal);

switch(u8PhsCrrectMode)
{
case (TIMER1_PHASECORRECT_PIN1A_CLEAR_SET):
	SET_BIT(TCCR1A_REG,7);CLR_BIT(TCCR1A_REG,6);//Clear The Pin1A At Up And Set At Down
	TIMER1_vidSetComparReg_ChannelA(u16CompareValue);
	break;

case (TIMER1_PHASECORRECT_PIN1A_SET_CLEAR):
	SET_BIT(TCCR1A_REG,7);SET_BIT(TCCR1A_REG,6);//Set The Pin1A At Up And Clear At Down
	TIMER1_vidSetComparReg_ChannelA(u16CompareValue);
	break;

case (TIMER1_PHASECORRECT_PIN1B_CLEAR_SET):
	SET_BIT(TCCR1A_REG,5);CLR_BIT(TCCR1A_REG,4);//Clear The Pin1B At Up And Set At Down
	TIMER1_vidSetComparReg_ChannelB(u16CompareValue);
	break;

case (TIMER1_PHASECORRECT_PIN1B_SET_CLEAR):
	SET_BIT(TCCR1A_REG,5);SET_BIT(TCCR1A_REG,4);//Set The Pin1B At Up And Clear At Down
	TIMER1_vidSetComparReg_ChannelB(u16CompareValue);
	break;

}

/**********************************************/
/******* Start Timing (CLOCK_SELECT)***********/
/**********************************************/
#if(CLOCK_SELECT == NO_CLK_OFF )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_NO_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_8_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_64_PRESCALER )
	CLR_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_256_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == CLK_1024_PRESCALER )
	SET_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_F_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);

#elif(CLOCK_SELECT == EXT_CLK_R_EDGE )
	SET_BIT(TCCR1B_REG,2);
	SET_BIT(TCCR1B_REG,1);
	SET_BIT(TCCR1B_REG,0);

#endif
}


void TIMER1_vidDisplayInputCaptureMode(u8 u8EdgeSel)
{
	switch (u8EdgeSel)
	{
	case TIMER1_IC_FALLING:CLR_BIT(TCCR1B_REG,6);break;
	case TIMER1_IC_RAISING:SET_BIT(TCCR1B_REG,6);break;
	}
	TIMER1_vidEnableInputCaptureInterrupt();
	TIMER1_vidStartTimer_OverFlowMode(0x00);
}


void TIMER1_vidSetInitReg(u16 u16InitVal)
{
	TCNT1H_REG = (u16InitVal>>8);
	TCNT1L_REG = u16InitVal;
}

void TIMER1_vidSetComparReg_ChannelA(u16 u16CompareValue)
{
	OCR1AH_REG = (u16CompareValue>>8);
	OCR1AL_REG = u16CompareValue;
}

void TIMER1_vidSetInputCaptureReg(u16 u16InputCapture)
{
	ICR1H_REG = (u16InputCapture>>8);
	ICR1L_REG = u16InputCapture;
}

void TIMER1_vidSetComparReg_ChannelB(u16 u16CompareValue)
{
	OCR1BH_REG = (u8)(u16CompareValue>>8);
	OCR1BL_REG = (u8)u16CompareValue;
}


u16 TIMER1_u16GetCounterReg(void)
{
	return(((u16)TCNT1L_REG)|(((u16)TCNT1H_REG)<<8));
}

u16 TIMER1_u16GetComparReg_ChannelA(void)
{
	return(((u16)OCR1AL_REG)|(((u16)OCR1AH_REG)<<8));
}

u16 TIMER1_u16GetComparReg_ChannelB(void)
{
	return(((u16)OCR1BL_REG)|(((u16)OCR1BH_REG)<<8));
}

u16 TIMER1_u16GetInputCaptureReg(void)
{
	return(((u16)ICR1L_REG)|(((u16)ICR1H_REG)<<8));
}


void TIMER1_vidEnableOverFlowInterrupt(void)
{	SET_BIT(SR_REG,7);  	//Global Interrupt

	SET_BIT(TIMSK_REG,2);
}

void TIMER1_vidEnableCompareMatchInterrupt_ChannelA(void)
{	SET_BIT(SR_REG,7);  	//Global Interrupt

	SET_BIT(TIMSK_REG,4);
}

void TIMER1_vidEnableCompareMatchInterrupt_ChannelB(void)
{	SET_BIT(SR_REG,7);  	//Global Interrupt

	SET_BIT(TIMSK_REG,3);
}

void TIMER1_vidEnableInputCaptureInterrupt(void)
{	SET_BIT(SR_REG,7);  	//Global Interrupt

	SET_BIT(TIMSK_REG,5);
}

void TIMER1_vidDisableOverFlowInterrupt(void)
{
	CLR_BIT(TIMSK_REG,2);
}

void TIMER1_vidDisableCompareMatchInterrupt_ChannelA(void)
{
	CLR_BIT(TIMSK_REG,4);
}

void TIMER1_vidDisableCompareMatchInterrupt_ChannelB(void)
{
	CLR_BIT(TIMSK_REG,3);
}


void TIMER1_vidDisableInputCaptureInterrupt(void)
{
	SET_BIT(TIMSK_REG,5);
}


void TIMER1_vidStopTimer(void)
{
	CLR_BIT(TCCR1B_REG,2);
	CLR_BIT(TCCR1B_REG,1);
	CLR_BIT(TCCR1B_REG,0);
}


void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	Timer1_OF_Call_Back();
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	Timer1_CTC_A_Call_Back();
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	Timer1_CTC_B_Call_Back();
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	Timer1_IC_Call_Back();
}
