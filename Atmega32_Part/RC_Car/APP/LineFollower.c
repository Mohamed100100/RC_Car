/*
 * LineFollower.c
 *
 *  Created on: Oct 18, 2025
 *      Author: Eng.Gemy
 */

#include "../HAL/IR_SENSOR_Driver/IR_Init.h"
#include "../LIB/STD_TYPES.h"

#include "LineFollower.h"


void vidLineFollowerInit(){
	IR_u8Init();
}

u8 lineFollowerDetect(){
	u8 leftIrRead;
	u8 centerIrRead;
	u8 rightIrRead;

	if(IR_u8ReadSensor(IR_SENSOR_LEFT,&leftIrRead) != IR_OK){
		return LINE_FOLLOWER_ERROR;
	}
	if(IR_u8ReadSensor(IR_SENSOR_CENTER,&centerIrRead) != IR_OK){
		return LINE_FOLLOWER_ERROR;
	}
	if(IR_u8ReadSensor(IR_SENSOR_RIGHT,&rightIrRead) != IR_OK){
		return LINE_FOLLOWER_ERROR;
	}

	if((leftIrRead == IR_NO_OBJECT)&&(centerIrRead == IR_OBJECT_DETECTED)&&(rightIrRead == IR_NO_OBJECT)){
		return LINE_FOLLOWER_FORWARD;
	}
	if((leftIrRead == IR_OBJECT_DETECTED)&&(centerIrRead == IR_NO_OBJECT)&&(rightIrRead == IR_NO_OBJECT)){
		return LINE_FOLLOWER_LEFT;
	}
	if((leftIrRead == IR_NO_OBJECT)&&(centerIrRead == IR_NO_OBJECT)&&(rightIrRead == IR_OBJECT_DETECTED)){
		return LINE_FOLLOWER_RIGHT;
	}
	if((leftIrRead == IR_OBJECT_DETECTED)&&(centerIrRead == IR_OBJECT_DETECTED)&&(rightIrRead == IR_NO_OBJECT)){
		return LINE_FOLLOWER_SLIGHT_LEFT;
	}
	if((leftIrRead == IR_NO_OBJECT)&&(centerIrRead == IR_OBJECT_DETECTED)&&(rightIrRead == IR_OBJECT_DETECTED)){
		return LINE_FOLLOWER_SLIGHT_RIGHT;
	}
	if((leftIrRead == IR_NO_OBJECT)&&(centerIrRead == IR_NO_OBJECT)&&(rightIrRead == IR_NO_OBJECT)){
		return LINE_FOLLOWER_STOP;
	}
	if((leftIrRead == IR_OBJECT_DETECTED)&&(centerIrRead == IR_OBJECT_DETECTED)&&(rightIrRead == IR_OBJECT_DETECTED)){
		return LINE_FOLLOWER_STOP;
	}

	return LINE_FOLLOWER_ERROR;

}
