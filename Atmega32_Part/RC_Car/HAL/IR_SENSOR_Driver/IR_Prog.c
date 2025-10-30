/*
 * IR_Prog.c
 *
 *  Created on: Oct 18, 2025
 *      Author: Eng.Gemy
 */


#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO_Driver/DIO_Int.h"
#include "IR_Config.h"
#include "IR_Init.h"

/* IR Sensor Configuration Array */
typedef struct {
	u8 port;
	u8 pin;
} IR_SensorConfig_t;

/* Sensor configuration array */
static const IR_SensorConfig_t IR_SensorConfig[IR_SENSOR_COUNT] = {
		{IR_SENSOR_1_PORT, IR_SENSOR_1_PIN},
		{IR_SENSOR_2_PORT, IR_SENSOR_2_PIN},
		{IR_SENSOR_3_PORT, IR_SENSOR_3_PIN}};

static u8 IR_u8ConvertToLogical(u8 Copy_u8RawValue);
static u8 IR_u8ReadRawSensor(u8 Copy_u8SensorNum);

u8 IR_u8Init(void)
{
	u8 Local_u8Index;

	/* Configure all IR sensor pins as inputs */
	for (Local_u8Index = 0; Local_u8Index < IR_SENSOR_COUNT; Local_u8Index++)
	{
		/* Set pin as input */
		DIO_vidSetPinDir(IR_SensorConfig[Local_u8Index].port,
				IR_SensorConfig[Local_u8Index].pin,
				DIO_INPUT);

		/* Enable pull-up resistor if configured */
#if IR_PULLUP_ENABLED == 1
		DIO_vidEnablePullUpRes(IR_SensorConfig[Local_u8Index].port,
				IR_SensorConfig[Local_u8Index].pin);
#endif
	}

	return IR_OK;
}

u8 IR_u8ReadSensor(u8 Copy_u8SensorNum, u8* Copy_pu8Value)
{
	u8 Local_u8RawValue;

	/* Check parameters */
	if (Copy_pu8Value == NULL)
	{
		return IR_INVALID_PARAMETER;
	}

	if (Copy_u8SensorNum >= IR_SENSOR_COUNT)
	{
		return IR_INVALID_PARAMETER;
	}

	/* Read raw sensor value */
	Local_u8RawValue = IR_u8ReadRawSensor(Copy_u8SensorNum);

	/* Convert to logical value based on sensor type */
	*Copy_pu8Value = IR_u8ConvertToLogical(Local_u8RawValue);

	return IR_OK;
}

/* Private Functions */

static u8 IR_u8ReadRawSensor(u8 Copy_u8SensorNum)
{
	return DIO_u8GetPinVal(IR_SensorConfig[Copy_u8SensorNum].port,
			IR_SensorConfig[Copy_u8SensorNum].pin);
}
static u8 IR_u8ConvertToLogical(u8 Copy_u8RawValue)
{
#if IR_SENSOR_LOGIC == IR_ACTIVE_LOW
	/* Active low: LOW = object detected */
	return (Copy_u8RawValue == 0) ? IR_OBJECT_DETECTED : IR_NO_OBJECT;
#else
	/* Active high: HIGH = object detected */
	return (Copy_u8RawValue == 1) ? IR_OBJECT_DETECTED : IR_NO_OBJECT;
#endif
}
