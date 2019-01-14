/*
 * user_tasks.h
 * (C) 2013, Freescale Semiconductor, Inc.
 *
 *  Created on: Sep 13, 2013
 *      Author: rmpe01
 */

#ifndef USER_TASKS_H_
#define USER_TASKS_H_

// This header file defines function prototypes for places at which code can be placed 
// by a developer evaluating the Freescale Xtrinsic Sensor Fusion Library for use with Xtrinsic sensors.
// This library build limits access to specific development boards pre-approved by Freescale.
// A second library build (available under separate license) provides much more control over board
// and MCU resources, but at a higher level of complexity.

void UserStartup(void);

void UserHighFrequencyTaskInit(void);
void UserHighFrequencyTaskRun(void);

void UserMediumFrequencyTaskInit(void);
void UserMediumFrequencyTaskRun(void);

#endif /* USER_TASKS_H_ */
