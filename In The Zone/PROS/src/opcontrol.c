/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

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
void operatorControl() { //User Control Function
	while (1) { //Beginning of Driver control loop.
		JSb5u = joystickGetDigital(1, 5, JOY_UP); //Declares 'JSb5u' variable used for Button Definitions.
		JSb5d = joystickGetDigital(1, 5, JOY_DOWN); //Sets 'JSb5d' variable to equal the value of the lower left bumper.
		JSb6u = joystickGetDigital(1, 6, JOY_UP); //Sets 'JSb6u' variable to equal the value of the upper right bumper.
		JSb6d = joystickGetDigital(1, 6, JOY_DOWN); //Sets 'JSb6d' variable to equal the value of the lower right bumper.
		JSb7u = joystickGetDigital(1, 7, JOY_UP); //Sets 'JSb7u' variable to equal the value of the top button in group 7.
		JSb7d = joystickGetDigital(1, 7, JOY_DOWN); //Sets 'JSb7d' variable to equal the value of the bottom button in group 7.
		JSb7l = joystickGetDigital(1, 7, JOY_LEFT); //Sets 'JSb7l' variable to equal the value of the left button in group 7.
		JSb7r = joystickGetDigital(1, 7, JOY_RIGHT); //Sets 'JSb7r' variable to equal the value of the right button in group 7.
		JSb8u = joystickGetDigital(1, 8, JOY_UP); //Sets 'JSb8u' variable to equal the value of the top button in group 8.
		JSb8d = joystickGetDigital(1, 8, JOY_DOWN); //Sets 'JSb8d' variable to equal the value of the bottom button in group 8.
		JSb8l = joystickGetDigital(1, 8, JOY_LEFT); //Sets 'JSb8l' variable to equal the value of the left button in group 8.
		JSb8r = joystickGetDigital(1, 8, JOY_RIGHT); //Sets 'JSb8r' variable to equal the value of the right button in group 8.
		JSleft = joystickGetAnalog(1, 3); //Sets left joystick y-axis to 'JSleft'
		JSright = joystickGetAnalog(1, 2); //Sets right joystick x-axis to 'JSright'
		//Variable definitions are in the while() loop to keep them updated as the robot is active.


		//TANK CONTROLS
		if (halfspeed == -1) {
			setDrive(JSleft, JSright); //Tells the left joystick to control left motors, and right joystick to control right motors.
		}
		if (halfspeed == 1) {
			setDrive(JSright/2, JSright/2);
		}
		//MANIPULATOR CONTROLS

		//Claw Control
		if (JSb8d == true && JSb8r == false && dev == 0) {
			setClaw(63); //When the bottom button in group 8 is pressed, open the claw.
		}
		if (JSb8r == true && JSb8d == false && dev == 0) {
			setClaw(-63); //When the right button in group 8 is pressed, close the claw.
		}
		if (JSb8d == false && JSb8r == false && dev == 0) { //Resets if neither are pressed.
			setClaw(0);
		}

		//Mobile Goal Pickup Control
		if (JSb5u == true && JSb5d == false && dev == 0) {
			setMobile(127); //When the upper left bumper is pressed, it will raise the mobile goal pickup.
		}
		if (JSb5d == true && JSb5u == false && dev == 0) {
			setMobile(-127); //When the lower left bumper is pressed, it will lower the mobile goal pickup.
		}
		if (JSb5d == false && JSb5u == false && dev == 0) { //Resets if neither are pressed.
			setMobile(0);
		}

		//Tower Control
		if (JSb6u == true && JSb6d == false && dev == 0) {
			setTower(127); //When the upper right bumper is pressed, it will move the tower forward.
		}
		if (JSb6d == true && JSb6u == false && dev == 0) {
			setTower(-127); //When the lower right bumper is pressed, it will move the tower in reverse.
		}
		if (JSb6d == false && JSb6u == false && dev == 0) { //Resets of neither are pressed.
			setTower(0);
		}
		devmode();
	} //End of Driver control loop.
}
