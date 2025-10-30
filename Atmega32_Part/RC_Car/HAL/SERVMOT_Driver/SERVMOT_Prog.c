/*
 * SERVMOT_Prog.c
 *
 *  Created on: Oct 16, 2025
 *      Author: Eng.Gemy
 */


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO_Driver/DIO_Int.h"
#include "../../MCAL/TIMER1_Driver/TIMER1_Init.h"
#include "SERVMOT_Init.h"
#include "SERVMOT_Config.h"


void SERVMOT_vidStartRotate(f32 f32Degree)
{
	static u8 Counter = 0;
	u16 u16Compare;

	if((f32Degree >= 0) && (f32Degree <= 180))
	{
		// Calculate compare value using exact working parameters
		if(f32Degree <= 90)
		{
			// 0° to 90°: map 0-90 to 65-175
			u16Compare = 65 + (u16)((f32Degree / 90.0) * 110.0);
		}
		else
		{
			// 90° to 180°: map 90-180 to 175-300
			u16Compare = 175 + (u16)(((f32Degree - 90.0) / 90.0) * 125.0);
		}

		if(Counter == 0)
		{
			TIMER1_vidInit();
			TIMER1_vidSetInputCaptureReg(2499);  // 20ms period

			switch(SERVO_MOTOR_PIN)
			{
			case (SERVMOT_PINA):
					DIO_vidSetPinDir(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
			TIMER1_vidStartTimer_PWMMode(0, u16Compare, TIMER1_PWM_PIN_CLEAR_SET, TIMER1_CHANNEL_A);
			break;
			case (SERVMOT_PINB):
					DIO_vidSetPinDir(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);
			TIMER1_vidStartTimer_PWMMode(0, u16Compare, TIMER1_PWM_PIN_CLEAR_SET, TIMER1_CHANNEL_B);
			break;
			}
			Counter = 1;
		}
		else
		{
			switch(SERVO_MOTOR_PIN)
			{
			case (SERVMOT_PINA):
            		TIMER1_vidSetComparReg_ChannelA(u16Compare);
			break;
			case (SERVMOT_PINB):
            		TIMER1_vidSetComparReg_ChannelB(u16Compare);
			break;
			}
		}
	}
}

void SERVMOT_vidStopRotate(void)
{
	TIMER1_vidStopTimer();
}
