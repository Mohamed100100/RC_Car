/*
 * ModesHandler.h
 *
 *  Created on: Oct 23, 2025
 *      Author: Eng.Gemy
 */

#ifndef APP_MODESHANDLER_H_
#define APP_MODESHANDLER_H_

#include "../LIB/STD_TYPES.h"

#define MODE1		('1')
#define MODE2		('2')
#define MODE3		('3')
#define MODE4		('4')
#define IDLE_MODE	('E')

#define FORWARD_DIRECTION		('F')
#define BACKWARD_DIRECTION		('B')
#define RIGHT_DIRECTION			('R')
#define LEFT_DIRECTION			('L')
#define STOP_MOVE				('S')

extern u8 selectedMode;

void handleMode1();
void handleMode2();
void handleMode3();
void handleMode4();
void handleIdleMode();
void carInit();

#endif /* APP_MODESHANDLER_H_ */
