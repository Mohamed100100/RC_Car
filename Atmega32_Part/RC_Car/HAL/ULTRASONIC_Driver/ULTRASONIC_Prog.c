/*
 * ULTRASONIC_Prog.c
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */
#include "ULTRASONIC_Init.h"
#include "ULTRASONIC_Config.h"
#include "../../MCAL/ICU_Driver/ICU_Init.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO_Driver/DIO_Int.h"
#include <util/delay.h>

/* Private Function Prototypes */
static void ULTRASONIC_voidSendTriggerPulse(void);
static u8 ULTRASONIC_u8ConvertTimeToDistance(u32 Copy_u32TimeUs, u16* Copy_pu16Distance);

u8 ULTRASONIC_u8Init(void)
{
	/* Initialize ICU */
	if (ICU_u8Init() != ICU_OK)
	{
		return ULTRASONIC_ERROR;
	}

	/* Configure trigger pin as output */
	DIO_vidSetPinDir(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_OUTPUT);
	DIO_vidSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_LOW);

	/* Wait for sensor to stabilize */
	_delay_ms(100);

	/* Make sure echo pin is input with pull-up */
	DIO_vidSetPinDir(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN, DIO_INPUT);
	DIO_vidEnablePullUpRes(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN);

	return ULTRASONIC_OK;
}



u8 ULTRASONIC_u8MeasureDistance(u16* Copy_pu16Distance)
{
	u8 Local_u8Status;
	u16 Local_u16Timeout = 3;

	if (Copy_pu16Distance == NULL)
	{
		return ULTRASONIC_ERROR;
	}

	/* Start measurement */
	Local_u8Status = ULTRASONIC_u8StartMeasurement();
	if (Local_u8Status != ULTRASONIC_OK)
	{
		return Local_u8Status;
	}

	/* Wait for measurement to complete */
	while (!ULTRASONIC_u8IsMeasurementComplete() && Local_u16Timeout > 0)
	{
		_delay_ms(10);
		Local_u16Timeout--;
	}

	if (Local_u16Timeout == 0)
	{
		ULTRASONIC_voidReset();
		return ULTRASONIC_TIMEOUT;
	}

	/* Get result */
	return ULTRASONIC_u8GetDistance(Copy_pu16Distance);
}

u8 ULTRASONIC_u8StartMeasurement(void)
{
	u8 Local_u8Status;
	u16 Local_u16EchoTimeout = 1000;

	/* Reset ICU first */
	ICU_voidReset();

	/* Wait for echo pin to be LOW before starting */
	while (DIO_u8GetPinVal(ULTRASONIC_ECHO_PORT, ULTRASONIC_ECHO_PIN) && Local_u16EchoTimeout > 0)
	{
		_delay_us(10);
		Local_u16EchoTimeout--;
	}

	if (Local_u16EchoTimeout == 0)
	{
		return ULTRASONIC_ERROR;
	}

	/* Send trigger pulse */
	ULTRASONIC_voidSendTriggerPulse();

	/* Wait longer for echo to start */
	_delay_us(100);

	/* Start ICU measurement */
	Local_u8Status = ICU_u8StartMeasurement();

	return (Local_u8Status == ICU_OK) ? ULTRASONIC_OK : ULTRASONIC_ERROR;
}

u8 ULTRASONIC_u8GetDistance(u16* Copy_pu16Distance)
{
	u32 Local_u32TimeUs;
	u8 Local_u8Status;

	if (Copy_pu16Distance == NULL)
	{
		return ULTRASONIC_ERROR;
	}

	/* Check if measurement is complete */
	if (!ICU_u8IsMeasurementComplete())
	{
		return ULTRASONIC_ERROR;
	}

	/* Get measured time */
	Local_u8Status = ICU_u8GetMeasuredTimeUs(&Local_u32TimeUs);
	if (Local_u8Status != ICU_OK)
	{
		return ULTRASONIC_ERROR;
	}

	/* Convert time to distance */
	return ULTRASONIC_u8ConvertTimeToDistance(Local_u32TimeUs, Copy_pu16Distance);
}

u8 ULTRASONIC_u8IsMeasurementComplete(void)
{
	return ICU_u8IsMeasurementComplete();
}

u8 ULTRASONIC_u8GetRawTime(u32* Copy_pu32TimeUs)
{
	if (Copy_pu32TimeUs == NULL)
	{
		return ULTRASONIC_ERROR;
	}

	if (!ICU_u8IsMeasurementComplete())
	{
		return ULTRASONIC_ERROR;
	}

	return ICU_u8GetMeasuredTimeUs(Copy_pu32TimeUs);
}

void ULTRASONIC_voidReset(void)
{
	ICU_voidReset();
}

/* Private Functions */

static void ULTRASONIC_voidSendTriggerPulse(void)
{
	/* Send 10us trigger pulse */
	DIO_vidSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_HIGH);
	_delay_us(ULTRASONIC_TRIGGER_TIME_US);
	DIO_vidSetPinVal(ULTRASONIC_TRIG_PORT, ULTRASONIC_TRIG_PIN, DIO_LOW);
}
static u8 ULTRASONIC_u8ConvertTimeToDistance(u32 Copy_u32TimeUs, u16* Copy_pu16Distance)
{
	u16 Local_u16Distance;

	/* Convert time to distance */
	/* Distance = (Time × Speed of Sound) / 2 */
	/* Speed of sound = 343 m/s = 0.0343 cm/us */
	/* Distance (cm) = (Time_us × 0.0343) / 2 = Time_us / 58.3 ≈ Time_us / 58 */
	Local_u16Distance = (u16)(2*Copy_u32TimeUs / 58);

	/* Check if distance is within valid range */
	if (Local_u16Distance < ULTRASONIC_MIN_DISTANCE)
	{
		return ULTRASONIC_OUT_OF_RANGE;
	}

	if (Local_u16Distance > ULTRASONIC_MAX_DISTANCE)
	{
		return ULTRASONIC_OUT_OF_RANGE;
	}

	*Copy_pu16Distance = Local_u16Distance;
	return ULTRASONIC_OK;
}
