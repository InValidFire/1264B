/*
 * motors.c
 *
 *  Basic motor controls for 1264B
 *
 *  Created on: Dec 5, 2017
 *      Author: Logan H.
 */

#include "main.h"

//	+ value makes motor forward powered
//	- value makes motor reverse powered
void setDrive(int left, int right) { //Sets base motors power.
	motorSet(MOTOR_LEFT_1, left); //Sets front-left motor power.
	motorSet(MOTOR_LEFT_2, left); //Sets back-left motor power.
	motorSet(MOTOR_RIGHT_1, -right); //Sets front-right motor power.
	motorSet(MOTOR_RIGHT_2, -right); //Sets back-right motor power.
}
void setManipulator(int power) { //Sets manipulator motors power.
  motorSet(MOTOR_MANIP_1, power); //Sets left-manipulator motor power.
  motorSet(MOTOR_MANIP_2, -power); //Sets right-manipulator motor power.
}
void PivotLeft(int power, int milsec) { //Pivots to the left.
  motorSet(MOTOR_LEFT_1, -power); //Sets front-left motor reverse power.
  motorSet(MOTOR_LEFT_2, -power); //Sets back-left motor reverse power.
  motorSet(MOTOR_RIGHT_1, power); //Sets front-right motor forward power.
  motorSet(MOTOR_RIGHT_2, power); //Sets back-right motor forward power.
  delay(milsec); //Repeats for set amount of time.
}
void PivotRight(int power, int milsec) { //Pivots to the right.
  motorSet(MOTOR_LEFT_1, power); //Sets front-left motor forward power.
  motorSet(MOTOR_LEFT_2, power); //Sets back-left motor forward power.
  motorSet(MOTOR_RIGHT_1, -power); //Sets front-right motor reverse power.
  motorSet(MOTOR_RIGHT_2, -power); //Sets back-right motor reverse power.
  delay(milsec); //Repeats for set amount of time.
}
