/*
 * motors.h
 *
 *  Motor port definitions for 1264B
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
#define MOTOR_LEFT_1	2 //Sets front-left motor to port 2.
#define MOTOR_LEFT_2	3 //Sets back-left motor to port 3.
#define MOTOR_RIGHT_1	4 //Sets front-right motor to port 4.
#define MOTOR_RIGHT_2	5 //Sets back-right motor to port 5.
/////////////////////////// MANIPULATOR MOTORS //////////////////////////////////
#define MOTOR_MANIP_1 6 //Sets left-manipulator motor to port 6.
#define MOTOR_MANIP_2 7 //Sets right-manipulator motor to port 7.
/////////////////////////// BASIC FUNCTIONS /////////////////////////////////////
void setDrive(int left, int right); //Sets base motors power.
void setManipulator(int power); //Sets manipulator motors power.
void PivotLeft(int power, int milsec); //Pivots to the left.
void PivotRight(int power, int milsec); //Pivots to the right.

#endif
