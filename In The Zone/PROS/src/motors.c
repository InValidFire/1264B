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

/////////////////////////// DRIVE CONTROL FUNCTIONS ///////////////////////////
void setDrive(int left, int right) { //Sets drivetrain motors power.
	motorSet(MOTOR_LEFT_FRONT, left); //Sets front-left motor power.
	motorSet(MOTOR_LEFT_MID, -left); //Sets mid-left motor power.
	motorSet(MOTOR_LEFT_BACK, left); //Sets back-left motor power.
	motorSet(MOTOR_RIGHT_FRONT, -right); //Sets front-right motor power.
	motorSet(MOTOR_RIGHT_MID, right); //Sets mid-right motor power.
	motorSet(MOTOR_RIGHT_BACK, -right); //Sets back-right motor power.
}
void setDriveTimed (int left, int right, int milsec) {
	motorSet(MOTOR_LEFT_FRONT, left); //Sets front-left motor power.
	motorSet(MOTOR_LEFT_MID, -left); //Sets mid-left motor power.
	motorSet(MOTOR_LEFT_BACK, left); //Sets back-left motor power.
	motorSet(MOTOR_RIGHT_FRONT, -right); //Sets front-right motor power.
	motorSet(MOTOR_RIGHT_MID, right); //Sets mid-right motor power.
	motorSet(MOTOR_RIGHT_BACK, -right); //Sets back-right motor power.
	delay(milsec);
}

/////////////////////////// MANIPULATOR FUNCTIONS ///////////////////////////
void setTower(int power) { //Sets tower motors power.
  motorSet(MOTOR_LEFT_TOWER, power); //Sets left-tower motor power.
  motorSet(MOTOR_RIGHT_TOWER, -power); //Sets right-tower motor power.
}
void setTowerTimed(int power, int milsec) {
	motorSet(MOTOR_LEFT_TOWER, power);
	motorSet(MOTOR_RIGHT_TOWER, -power);
	delay(milsec);
}
void setClaw(int power) {//Sets claw motor power.
	motorSet(MOTOR_CLAW, power); //Sets claw motor power.
}
void setClawTimed(int power, int milsec) {//Sets claw motor power for a set amount of time.
	motorSet(MOTOR_CLAW, power); //Sets claw motor power.
	delay(milsec); //Repeats for a set amount of time.
}
void setMobile(int power) { //Sets mobile goal motor power.
	motorSet(MOTOR_MOBILE_GOAL, power); //Sets mobile goal motor power.
}
void setMobileTimed(int power, int milsec) { //Sets mobile goal motor power for a set amount of time.
	motorSet(MOTOR_MOBILE_GOAL, power); //Sets mobile goal power.
	delay(milsec); //Repeats for a set amount of time.
}
////////////////////////// TURNING FUNCTIONS ///////////////////////////////////
void pivotLeft(int power) { //Pivots to the left.
	motorSet(MOTOR_LEFT_FRONT, -power); //Sets front-left motor reverse power.
	motorSet(MOTOR_LEFT_MID, power); //Sets mid-left motor forward power.
	motorSet(MOTOR_LEFT_BACK, -power); //Sets back-left motor reverse power.
	motorSet(MOTOR_RIGHT_FRONT, power); //Sets front-right motor forward power.
	motorSet(MOTOR_RIGHT_MID, -power); //Sets mid-right motor reverse power.
	motorSet(MOTOR_RIGHT_BACK, power); //Sets back-right motor forward power.
}
void pivotLeftTimed(int power, int milsec) { //Pivots to the left for a set amount of time.
	motorSet(MOTOR_LEFT_FRONT, -power); //Sets front-left motor reverse power.
	motorSet(MOTOR_LEFT_MID, power); //Sets mid-left motor forward power.
	motorSet(MOTOR_LEFT_BACK, -power); //Sets back-left motor reverse power.
	motorSet(MOTOR_RIGHT_FRONT, power); //Sets front-right motor forward power.
	motorSet(MOTOR_RIGHT_MID, -power); //Sets mid-right motor reverse power.
	motorSet(MOTOR_RIGHT_BACK, power); //Sets back-right motor forward power.
  delay(milsec); //Repeats for set amount of time.
}
void pivotRight(int power) { //Pivots to the right.
	motorSet(MOTOR_LEFT_FRONT, power); //Sets front-left motor forward power.
	motorSet(MOTOR_LEFT_MID, -power); //Sets mid-left motor reverse power.
	motorSet(MOTOR_LEFT_BACK, power); //Sets back-left motor forward power.
	motorSet(MOTOR_RIGHT_FRONT, -power); //Sets front-right motor reverse power.
	motorSet(MOTOR_RIGHT_MID, power); //Sets mid-right motor forward power.
	motorSet(MOTOR_RIGHT_BACK, -power); //Sets back-right motor reverse power.
}
void pivotRightTimed(int power, int milsec) { //Pivots to the right for a set amount of time.
	motorSet(MOTOR_LEFT_FRONT, power); //Sets front-left motor forward power.
	motorSet(MOTOR_LEFT_MID, -power); //Sets mid-left motor reverse power.
	motorSet(MOTOR_LEFT_BACK, power); //Sets back-left motor forward power.
	motorSet(MOTOR_RIGHT_FRONT, -power); //Sets front-right motor reverse power.
	motorSet(MOTOR_RIGHT_MID, power); //Sets mid-right motor forward power.
	motorSet(MOTOR_RIGHT_BACK, -power); //Sets back-right motor reverse power.
  delay(milsec); //Repeats for set amount of time.
}
