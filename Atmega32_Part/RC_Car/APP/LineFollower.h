/*
 * LineFollower.h
 *
 *  Created on: Oct 18, 2025
 *      Author: Eng.Gemy
 */

#ifndef APP_LINEFOLLOWER_H_
#define APP_LINEFOLLOWER_H_


#define LINE_FOLLOWER_ERROR 			(0)
#define LINE_FOLLOWER_FORWARD			(1)
#define LINE_FOLLOWER_LEFT				(2)
#define LINE_FOLLOWER_RIGHT				(3)
#define LINE_FOLLOWER_SLIGHT_LEFT		(4)
#define LINE_FOLLOWER_SLIGHT_RIGHT		(5)
#define LINE_FOLLOWER_STOP				(6)


void vidLineFollowerInit();
u8 lineFollowerDetect();

#endif /* APP_LINEFOLLOWER_H_ */
