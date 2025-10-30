/*
 * Direction.c
 *
 *  Created on: Oct 16, 2025
 *      Author: Eng.Gemy
 */

#include "CarMove.h"

#include "../HAL/DCMOT_Driver/DCMOT_Init.h"
void vdCarMoveUp(){
	DCMOT_1_vidRotCCW();
	DCMOT_2_vidRotCCW();
}

void vdCarInitMotors(){
	DCMOT_1_vidInit();
	DCMOT_2_vidInit();
}

void vdCarMoveBack(){
	DCMOT_1_vidRotCW();
	DCMOT_2_vidRotCW();
}

void vdCarMoveRight(){
	DCMOT_1_vidRotCCW();
	DCMOT_2_vidStop();
}

void vdCarMoveLeft(){
	DCMOT_2_vidRotCCW();
	DCMOT_1_vidStop();
}

void vdCarStop(){
	DCMOT_1_vidStop();
	DCMOT_2_vidStop();
}

