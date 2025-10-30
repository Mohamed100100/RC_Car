/*
 * IR_Init.h
 *
 *  Created on: Oct 18, 2025
 *      Author: Eng.Gemy
 */

#ifndef IR_INIT_H_
#define IR_INIT_H_

#include "../../LIB/STD_TYPES.h"

/* IR Sensor Status */
#define IR_OK                   0
#define IR_ERROR                1
#define IR_INVALID_PARAMETER    2

/* IR Sensor Logic Types */
#define IR_ACTIVE_LOW           0
#define IR_ACTIVE_HIGH          1

/* IR Sensor States */
#define IR_OBJECT_DETECTED      1
#define IR_NO_OBJECT            0

#define IR_SENSOR_LEFT			0
#define IR_SENSOR_CENTER		1
#define IR_SENSOR_RIGHT			2

/* Function Prototypes */

/**
 * @brief Initialize IR sensor system
 * @return u8 - Status code
 */
u8 IR_u8Init(void);

/**
 * @brief Read single IR sensor
 * @param Copy_u8SensorNum - Sensor number (0 to IR_SENSOR_COUNT-1)
 * @param Copy_pu8Value - Pointer to store sensor value
 * @return u8 - Status code
 */
u8 IR_u8ReadSensor(u8 Copy_u8SensorNum, u8* Copy_pu8Value);

#endif /* IR_INIT_H_ */
