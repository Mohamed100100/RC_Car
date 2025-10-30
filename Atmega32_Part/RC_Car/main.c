/*
 * main.c
 *
 *  Created on: Oct 14, 2025
 *      Author: Eng.Gemy
 */

#define F_C	PU         8000000UL

#include "APP/ModesHandler.h"

int main(void)
{
	/* Main loop */
	while(1)
	{
		switch(selectedMode){
		case MODE1     : handleMode1();break;
		case MODE2     : handleMode2();break;
		case MODE3     : handleMode3();break;
		case MODE4     : handleMode4();break;
		case IDLE_MODE : handleIdleMode();break;
		}
	}

	return 0;
}
