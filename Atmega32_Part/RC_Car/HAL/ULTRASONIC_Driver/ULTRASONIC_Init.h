/*
 * ULTRASONIC_Init.h
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */
#ifndef ULTRASONIC_INIT_H_
#define ULTRASONIC_INIT_H_

#include "../../LIB/STD_TYPES.h"

/* Ultrasonic Status */
#define ULTRASONIC_OK               0
#define ULTRASONIC_ERROR            1
#define ULTRASONIC_TIMEOUT          2
#define ULTRASONIC_OUT_OF_RANGE     3
#define ULTRASONIC_BUSY             4

/* Function Prototypes */

/**
 * @brief Initialize ultrasonic sensor
 * @return u8 - Status code
 */
u8 ULTRASONIC_u8Init(void);

/**
 * @brief Measure distance in centimeters (blocking)
 * @param Copy_pu16Distance - Pointer to store distance in cm
 * @return u8 - Status code
 */
u8 ULTRASONIC_u8MeasureDistance(u16* Copy_pu16Distance);

/**
 * @brief Start non-blocking distance measurement
 * @return u8 - Status code
 */
u8 ULTRASONIC_u8StartMeasurement(void);

/**
 * @brief Get distance result (non-blocking)
 * @param Copy_pu16Distance - Pointer to store distance in cm
 * @return u8 - Status code
 */
u8 ULTRASONIC_u8GetDistance(u16* Copy_pu16Distance);

/**
 * @brief Check if measurement is complete
 * @return u8 - 1 if complete, 0 if measuring
 */
u8 ULTRASONIC_u8IsMeasurementComplete(void);

/**
 * @brief Get raw measurement time in microseconds
 * @param Copy_pu32TimeUs - Pointer to store time in microseconds
 * @return u8 - Status code
 */
u8 ULTRASONIC_u8GetRawTime(u32* Copy_pu32TimeUs);

/**
 * @brief Reset sensor to idle state
 */
void ULTRASONIC_voidReset(void);

#endif /* ULTRASONIC_INIT_H_ */
