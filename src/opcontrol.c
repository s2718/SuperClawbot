/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "home.h"
#include "joystickPIDControl.h"
#include "kinematics.h"
#include "stabilizeControl.h"
#include "paths.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl() {

	Encoder encoderShoulder = encoderInit(8, 9, true);
  Encoder encoderElbow = encoderInit(6, 7, false);
	Ultrasonic ultrasonic = ultrasonicInit(1,2);

	home(encoderElbow, encoderShoulder);
	// int x = (int)L1-20;
	// int z = (int)L2+10;

	// printf("elbow%d\n",(int)upperElbow(x,z) );
	// printf("shoulder%d\n",(int)upperShoulder(x,z) );
	printf("started PID\n");
	// for (int i = 0; i < 60; i+= 1){
	// PIDContol(encoderElbow, encoderShoulder, (int)upperElbow(x + i,z), (int)upperShoulder(x + i,z));
	// }
	PIDPathContol(encoderElbow,  encoderShoulder);
	printf("finished PID\n");
	stabilizeControl(encoderElbow, encoderShoulder);
	// while(true) {
	// 	i ++;
	// 	z += 5;
	// 	if (i%10 == 0) {
	// 		z -= 50;
	// 	}
	// 	elbowTarget = (int)upperElbow(x,z);
	// 	shoulderTarget = (int)upperShoulder(x,z);
	// 	PIDContol(encoderElbow, encoderShoulder, elbowTarget, shoulderTarget);
	// 	printf("%d\n",i);
	// }
}
