/*
 * Eyes.h
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */

#ifndef APP_EYES_H_
#define APP_EYES_H_

#include "../LIB/STD_TYPES.h"


#define EYES_RIGHT_ANGLE	(0)
#define EYES_LEFT_ANGLE		(180)
#define EYES_FORWAFD_ANGLE	(90)

#define EYES_MEASURE_OK		(1)
#define EYES_MEASURE_ERROR	(0)

#define EYES_THRESHOLD		(40)

// it will be used when no obstacle in front off the car
#define EYES_MEASURE_FAR_NUM	(10000)

void EYES_vdInit();
void EYES_LookRight();
void EYES_LookLeft();
void EYES_LookForward();
u8 EYES_MeasureDist(u16* u16Distance);
void EYES_SetAlarm();




#endif /* APP_EYES_H_ */
