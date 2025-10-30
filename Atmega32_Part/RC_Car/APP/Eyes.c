/*
 * Eyes.c
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */


#include "../LIB/STD_TYPES.h"
#include "../HAL/SERVMOT_Driver/SERVMOT_Init.h"
#include "../HAL/ULTRASONIC_Driver/ULTRASONIC_Init.h"

#include "Eyes.h"

void EYES_vdInit(){
	/* initialze servo motor */
	SERVMOT_vidStartRotate(EYES_FORWAFD_ANGLE);

	/* initialize ultrasonic sensor */
	ULTRASONIC_u8Init();
}

void EYES_LookRight(){
	SERVMOT_vidStartRotate(EYES_RIGHT_ANGLE);
}

void EYES_LookLeft(){
	SERVMOT_vidStartRotate(EYES_LEFT_ANGLE);
}

void EYES_LookForward(){
	SERVMOT_vidStartRotate(EYES_FORWAFD_ANGLE);
}


u8 EYES_MeasureDist(u16* u16Distance){
	u16 distance;
	u8 status;

	if(u16Distance == NULL){
		return EYES_MEASURE_ERROR;
	}

	/* Measure distance */
	status = ULTRASONIC_u8MeasureDistance(&distance);

	switch(status)
	{
	case ULTRASONIC_OK:
		*u16Distance = distance;
		status = EYES_MEASURE_OK;
		break;

	case ULTRASONIC_TIMEOUT:
		*u16Distance = EYES_MEASURE_FAR_NUM;
		status = EYES_MEASURE_OK;
		break;

	case ULTRASONIC_OUT_OF_RANGE:
		*u16Distance = 0;
		status = EYES_MEASURE_OK;
		break;

	case ULTRASONIC_ERROR:
		status = EYES_MEASURE_ERROR;
		break;

	default:
		status = EYES_MEASURE_ERROR;
		break;
	}
	return (status);
}

void EYES_SetAlarm(){
	// here i can at the hardware certain pin connected to led or bazzar to sit it when error happen
}
