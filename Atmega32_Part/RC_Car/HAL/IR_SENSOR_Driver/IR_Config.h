/*
 * IR_Config.h
 *
 *  Created on: Oct 18, 2025
 *      Author: Eng.Gemy
 */

#ifndef IR_CONFIG_H_
#define IR_CONFIG_H_

/* IR Sensor Configuration */

/* Number of IR sensors */
#define IR_SENSOR_COUNT         3

/* IR Sensor 1 (Left) */
#define IR_SENSOR_1_PORT        DIO_PORTA
#define IR_SENSOR_1_PIN         DIO_PIN4

/* IR Sensor 2 (Center) */
#define IR_SENSOR_2_PORT        DIO_PORTA
#define IR_SENSOR_2_PIN         DIO_PIN5

/* IR Sensor 3 (Right) */
#define IR_SENSOR_3_PORT        DIO_PORTA
#define IR_SENSOR_3_PIN         DIO_PIN6


/* IR Sensor Logic Configuration */
/* Set according to your IR sensor type:
 * IR_ACTIVE_LOW  - Sensor outputs LOW when object detected
 * IR_ACTIVE_HIGH - Sensor outputs HIGH when object detected
 */
#define IR_SENSOR_LOGIC         IR_ACTIVE_HIGH

/* Pull-up Resistor Configuration */
#define IR_PULLUP_ENABLED       1   /* 1 = Enable, 0 = Disable */

/* Debounce Configuration */
#define IR_DEBOUNCE_ENABLED     1   /* 1 = Enable, 0 = Disable */
#define IR_DEBOUNCE_TIME_MS     10  /* Debounce time in milliseconds */

#endif /* IR_CONFIG_H_ */
