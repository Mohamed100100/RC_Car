/*
 * ModesHandler.c
 *
 *  Created on: Oct 23, 2025
 *  Author: Eng.Gemy
 *
 *  Description:
 *  This file handles different operating modes of the RC car project.
 *  Each mode defines a specific car behavior, such as:
 *    - Manual control using UART commands (Mode 1)
 *    - Obstacle avoidance using ultrasonic sensor (Mode 2)
 *    - Line following using IR sensors (Mode 3)
 *    - Reserved mode for future expansion (Mode 4)
 *    - Idle mode when no active command (Mode 'E')
 *
 *  The system uses UART interrupts to receive mode and direction commands
 *  asynchronously from the ESP32 or external controller.
 */

#include "../LIB/STD_TYPES.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "../MCAL/UART_Driver/UART_Init.h"
#include "CarMove.h"
#include "Eyes.h"
#include "LineFollower.h"
#include "ModesHandler.h"

/* ========== GLOBAL VARIABLES ========== */

/*
 * selectedMode:
 *  Stores the current operating mode of the car.
 *  Can be: '1', '2', '3', '4', or 'E' (for idle).
 */
u8 selectedMode = IDLE_MODE;

/*
 * SelectedDirec:
 *  Stores the current direction command received from the UART.
 *  Can be: 'F', 'B', 'L', 'R', or 'S' (for stop).
 */
u8 SelectedDirec = STOP_MOVE;

/* UART RX interrupt callback prototype */
void SimpleRxCallback(u8 data);

/* ================================================================
 * Function: carInit()
 * ---------------------------------------------------------------
 * Description:
 *  Initializes all the car peripherals and modules.
 *  - Initializes UART and assigns the RX interrupt callback.
 *  - Initializes motors, ultrasonic sensor (Eyes), and line follower sensors.
 *  - Enables global interrupts.
 *  - Stops the car initially.
 * ================================================================ */
void carInit() {
	UART_voidSetRxCallback(SimpleRxCallback);  // Set UART interrupt handler
	UART_vidInit();                            // Initialize UART
	vdCarInitMotors();                         // Initialize motor driver pins
	EYES_vdInit();                             // Initialize ultrasonic (eyes)
	vidLineFollowerInit();                     // Initialize line follower sensors
	vdCarStop();                               // Stop motors initially
	sei();                                     // Enable global interrupts
}

/* ================================================================
 * Function: handleMode1()
 * ---------------------------------------------------------------
 * Description:
 *  Handles manual control mode.
 *  The car moves according to direction commands received from UART.
 * ================================================================ */
void handleMode1() {
	switch(SelectedDirec) {
	case FORWARD_DIRECTION  : vdCarMoveUp();    break;
	case BACKWARD_DIRECTION : vdCarMoveBack();  break;
	case RIGHT_DIRECTION    : vdCarMoveRight(); break;
	case LEFT_DIRECTION     : vdCarMoveLeft();  break;
	case STOP_MOVE          : vdCarStop();      break;
	}
}

/* ================================================================
 * Function: handleMode2()
 * ---------------------------------------------------------------
 * Description:
 *  Handles autonomous obstacle avoidance mode using ultrasonic sensor.
 *  The car:
 *    - Moves forward if no obstacle is detected within EYES_THRESHOLD distance.
 *    - Stops and makes a decision (turn left/right) if an obstacle is close.
 *    - Moves backward slightly if too close to the obstacle.
 * ================================================================ */
void handleMode2() {
	u16 distance = 0;

	// Measure front distance
	if (EYES_MeasureDist(&distance) != EYES_MEASURE_OK) {
		EYES_SetAlarm();  // Trigger error/alarm (e.g., LED)
		return;
	}

	// If no obstacle in front — move forward
	if (distance > EYES_THRESHOLD) {
		vdCarMoveUp();
	} else {
		// Stop and decide a new direction
		vdCarStop();
		_delay_ms(600);

		// Too close — move backward slightly
		if (distance < 15) {
			vdCarMoveBack();
			_delay_ms(300);
			vdCarStop();
		}

		// Scan right side
		EYES_LookRight();
		_delay_ms(600);
		u16 rightDist;
		if (EYES_MeasureDist(&rightDist) != EYES_MEASURE_OK) {
			EYES_SetAlarm();
			return;
		}

		// Scan left side
		EYES_LookLeft();
		_delay_ms(600);
		u16 leftDist;
		if (EYES_MeasureDist(&leftDist) != EYES_MEASURE_OK) {
			EYES_SetAlarm();
			return;
		}

		// Compare left and right distances
		if (rightDist > leftDist) {
			// More space on the right — turn right
			vdCarMoveRight();
			_delay_ms(300);
		} else {
			// More space on the left — turn left
			vdCarMoveLeft();
			_delay_ms(300);
		}

		vdCarStop();
		EYES_LookForward();  // Reset servo to forward direction
		_delay_ms(300);
	}
}

/* ================================================================
 * Function: handleMode3()
 * ---------------------------------------------------------------
 * Description:
 *  Handles line-following mode.
 *  Uses the three IR sensors to detect line position and control direction.
 *  Based on the detected pattern, the car makes small corrections or turns.
 * ================================================================ */
void handleMode3() {
	u8 u8LineFollowerDirec = lineFollowerDetect();  // Read direction from sensors

	switch (u8LineFollowerDirec) {
	case LINE_FOLLOWER_FORWARD:	    vdCarMoveUp(); vdCarStop(); break;
	case LINE_FOLLOWER_LEFT:	    vdCarMoveLeft(); vdCarStop(); break;
	case LINE_FOLLOWER_RIGHT:	    vdCarMoveRight(); vdCarStop(); break;
	case LINE_FOLLOWER_SLIGHT_LEFT:	vdCarMoveLeft(); vdCarStop(); break;
	case LINE_FOLLOWER_SLIGHT_RIGHT:vdCarMoveRight(); vdCarStop(); break;
	case LINE_FOLLOWER_STOP:	    vdCarStop(); break;
	case LINE_FOLLOWER_ERROR:        vdCarStop(); break;
	default:                        vdCarStop(); break;
	}
}

/* ================================================================
 * Function: handleMode4()
 * ---------------------------------------------------------------
 * Description:
 *  Reserved for future features such as maze-solving or path memorization.
 * ================================================================ */
void handleMode4() {
	// Future extension: Maze solving, path learning, etc.
}

/* ================================================================
 * Function: handleIdleMode()
 * ---------------------------------------------------------------
 * Description:
 *  Puts the car in a safe idle state:
 *    - Stops all motors
 *    - Centers the ultrasonic servo (eyes)
 * ================================================================ */
void handleIdleMode() {
	vdCarStop();
	EYES_LookForward();
}

/* ================================================================
 * Function: SimpleRxCallback(u8 data)
 * ---------------------------------------------------------------
 * Description:
 *  UART interrupt callback function.
 *  Called automatically whenever a new byte is received via UART.
 *  Updates the mode or direction variables depending on the data.
 * ================================================================ */
void SimpleRxCallback(u8 data)
{
	switch(data) {
	// Mode selection commands
	case MODE1: selectedMode = MODE1; SelectedDirec = STOP_MOVE; break; // Manual
	case MODE2: selectedMode = MODE2; break;                      		// Obstacle Avoidance
	case MODE3: selectedMode = MODE3; break;                      		// Line Follower
	case MODE4: selectedMode = MODE4; break;                      		// Reserved
	case IDLE_MODE: selectedMode = IDLE_MODE; break;              		// Idle

	// Direction control (used only in Mode 1)
	case FORWARD_DIRECTION: SelectedDirec = FORWARD_DIRECTION; break;
	case BACKWARD_DIRECTION: SelectedDirec = BACKWARD_DIRECTION; break;
	case LEFT_DIRECTION: SelectedDirec = LEFT_DIRECTION; break;
	case RIGHT_DIRECTION: SelectedDirec = RIGHT_DIRECTION; break;
	case STOP_MOVE: SelectedDirec = STOP_MOVE; break;
	}
}
