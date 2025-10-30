/*
 * ULTRASONIC_Config.h
 *
 *  Created on: Oct 17, 2025
 *      Author: Eng.Gemy
 */
#ifndef ULTRASONIC_CONFIG_H_
#define ULTRASONIC_CONFIG_H_

/* Ultrasonic Sensor Configuration using ICU and DIO */

/* Trigger Pin Configuration */
#define ULTRASONIC_TRIG_PORT    DIO_PORTB									//red
#define ULTRASONIC_TRIG_PIN     DIO_PIN0

/* Echo Pin Configuration (must match ICU external interrupt pin) */
#define ULTRASONIC_ECHO_PORT    DIO_PORTD									//بنفسجي
#define ULTRASONIC_ECHO_PIN     DIO_PIN2   /* INT0 pin */

/* Measurement Parameters */
#define ULTRASONIC_MAX_DISTANCE     400    /* Maximum distance in cm */
#define ULTRASONIC_MIN_DISTANCE     2      /* Minimum distance in cm */

/* Timing Parameters */
#define ULTRASONIC_TRIGGER_TIME_US  10     /* 10us trigger pulse */
#define ULTRASONIC_TIMEOUT_MS       10    /* Measurement timeout */

#endif /* ULTRASONIC_CONFIG_H_ */
