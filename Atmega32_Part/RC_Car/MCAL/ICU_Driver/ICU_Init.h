/*
 * ICU_Init.h
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */

#ifndef ICU_INIT_H_
#define ICU_INIT_H_

#include "../../LIB/STD_TYPES.h"

/* ICU States */
#define ICU_STATE_IDLE          0
#define ICU_STATE_MEASURING     1
#define ICU_STATE_COMPLETE      2

/* ICU Status */
#define ICU_OK                  0
#define ICU_ERROR               1
#define ICU_TIMEOUT             2
#define ICU_BUSY                3

/* Function Prototypes */

/**
 * @brief Initialize ICU module
 * @return u8 - Status code
 */
u8 ICU_u8Init(void);

/**
 * @brief Start time measurement
 * @return u8 - Status code
 */
u8 ICU_u8StartMeasurement(void);

/**
 * @brief Stop current measurement
 * @return u8 - Status code
 */
u8 ICU_u8StopMeasurement(void);

/**
 * @brief Get measured time in Timer0 counts
 * @param Copy_pu32Time - Pointer to store measured time
 * @return u8 - Status code
 */
u8 ICU_u8GetMeasuredTime(u32* Copy_pu32Time);

/**
 * @brief Get measured time in microseconds
 * @param Copy_pu32TimeUs - Pointer to store time in microseconds
 * @return u8 - Status code
 */
u8 ICU_u8GetMeasuredTimeUs(u32* Copy_pu32TimeUs);

/**
 * @brief Check if measurement is complete
 * @return u8 - 1 if complete, 0 if measuring
 */
u8 ICU_u8IsMeasurementComplete(void);

/**
 * @brief Get current ICU state
 * @return u8 - Current state
 */
u8 ICU_u8GetState(void);

/**
 * @brief Reset ICU to idle state
 */
void ICU_voidReset(void);

#endif /* ICU_INIT_H_ */
