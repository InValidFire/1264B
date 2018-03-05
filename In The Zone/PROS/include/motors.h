/*
 * motors.h
 *
 *  Motor port definitions and function prototypes for 1264B
 *
 *  Created on: Dec 5, 2017
 *      Author: Logan H.
 */

#ifndef MOTORS_H_
#define MOTORS_H_

/********************************************************************************
 *                                                                              *
 *                          MOTOR DEFINITIONS                                   *
 *                                                                              *
*********************************************************************************/

/////////////////////////// DRIVE MOTORS ////////////////////////////////////////
#define MOTOR_RIGHT_FRONT 1 //Sets front-right motor to port 1.
#define MOTOR_RIGHT_MID	2 //Sets mid-right motor to port 2.
#define MOTOR_RIGHT_BACK	3 //Sets back-right motor to port 3.
#define MOTOR_LEFT_FRONT	4 //Sets front-left motor to port 4.
#define MOTOR_LEFT_MID	5 //Sets mid-left motor to port 5.
#define MOTOR_LEFT_BACK 6 //Sets back-left motor to port 6.

/////////////////////////// MANIPULATOR MOTORS //////////////////////////////////
#define MOTOR_MOBILE_GOAL 7 //Sets mobile goal pickup motor to port 7

#define MOTOR_CLAW 8 //Sets claw motor to port 8

#define MOTOR_LEFT_TOWER 9 //Sets left-tower motor to port 9
#define MOTOR_RIGHT_TOWER 10 //Sets right-tower motor to port 10

/////////////////////////// FUNCTIONS /////////////////////////////////////

// Drivetrain functions
void setDrive(int left, int right); //Sets base motors power.
void setDriveTimed(int left, int right, int milsec); //Sets base motors power for a set amount of time.

void pivotLeft (int power); //Pivots to the left
void pivotLeftTimed(int power, int milsec); //Pivots to the left for a set amount of time.

void pivotRight (int power);
void pivotRightTimed(int power, int milsec); //Pivots to the right for a set amount of time.

// Manipulator Functions
void setTower(int power); //Sets manipulator motors power.
void setTowerTimed(int power, int milsec); //Sets manipulator motors power for a set amount of time.

void setClaw(int power); //Sets claw motor power.
void setClawTimed(int power, int milsec); //Sets claw motor power for a set amount of time.

void setMobile(int power); //Sets mobile goal pickup motor power.
void setMobileTimed(int power, int milsec); //Sets mobile goal pickup motor power for a set amount of time.

//////////////////////////////////////////////////////////////////////////////////
#endif
