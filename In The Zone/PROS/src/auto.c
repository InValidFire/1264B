/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */
void autonomous() {
  int autover; //Sets variable for autonomous version.
  autover = 1; //Sets autover to 1. Change this to change loaded autonomous operation.
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  COMPETITION OPS:     SKILLS OPS:                       *
   *  DROP-OFF = auto1     SKILLFUL = auto2                  *
   *                                                         *
   *  TESTING OPS:                                           *
   *  ENCODER-TEST = auto3                                                       *
   *                                                         *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
  //////////////////////////////// AUTONOMOUS OPERATIONS ////////////////////////////////

  if(autover == 1) {
    auto1(); //Runs code in autovers.c
    }

  if(autover == 2) {
    auto2(); //Runs code in autovers.c
    }

  if(autover == 3) {
    auto3(); //Runs code in autovers.c
    }
  if (dev == 1) {
    operatorControl();
  }
}
