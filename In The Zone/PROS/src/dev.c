/*
 * dev.c
 *
 *  Developer Function Definition
 *
 *  Created on: Jan 25, 2018
 *      Author: Logan H.
 */
 #include <main.h>
void devmode() {
  //////////////////// DEVMODE ///////////////////////////
  // Developer Mode Toggle
  if (JSb8u == true && JSb7u == true) { //When both 8U and 7U are pressed, turn Devmode on.
    dev = dev*-1;
  }

  // Autonomous Test Control
  if (JSb7l == true && dev == 1 && speedtest == -1) { //When 7L is pressed, run the autonomous.
    autonomous();
  }

  //Pivot Controls
  if (JSb5u == true && dev == 1 && speedtest == -1) { //When the upper left bumper is pressed, pivot left.
    pivotLeft(127);
  }
  if(JSb6u == true && dev == 1 && speedtest == -1) { //When the upper right bumper is pressed, pivot right.
    pivotRight(127);
  }

  //Half Speed
  if (JSb7d == true && dev == 1 && speedtest == -1) { //When 7D is pressed, turn halfspeed (Soon to be Power Saver) on.
    halfspeed = 1;
  }

  ////////////// Speedtest /////////////////

  /* Plan for speedtest:
   * Use it for testing motors at different speeds, handy for building autonomous programs.
   */

  if (JSb7u == true && dev == 1) { //When 7U is pressed, toggle speedtest mode.
    speedtest = speedtest*-1; //Toggle switch by multiplying
  }

// LCD Setup for Speedtest.
  if (speedtest == 1 && dev == 1) { //While Speedtest and Devmode are active, show data on line 1.
    if(st_top == 1) { //If the st_top value is one, show data on line 1. (st_top is changed by LCD_BTN_MIDDLE)
      lcdPrint(uart1, 1, "Speed: %i       ", st_speed); //Shows speed on line 1 of LCD
    }
    if(st_top == -1) { //If the st_top value is negative one, show data on line 1
      lcdPrint(uart1, 1, "Time: %i        ", st_time);
    }

    //Menu controls for mode selection
    if (lcdReadButtons(uart1) == LCD_BTN_RIGHT) {
      st_mode = st_mode+1; //When right LCD btn is pressed, add one to st_mode
    }
    if (lcdReadButtons(uart1) == LCD_BTN_LEFT) { //When left LCD btn is pressed, subtract one from st_mode.
      st_mode = st_mode-1;
    }
    if (lcdReadButtons(uart1) == LCD_BTN_CENTER) { //When middle LCD btn is pressed, multiply st_top by -1, inverting the value as if it were a boolean.
      st_top = st_top*-1;
    }

    //Mode functions
    if (st_mode == 1) { //Only works if st_mode is 1
      lcdSetText(uart1, 2, "Mode: Drivetrain"); //Displays mode on LCD to avoid utter confusion from user.
      if(JSb7r == true) { //If 7R is pressed
        setDriveTimed(st_speed, st_speed, st_time); //Drives forward at whatever the st_speed and st_time are set to.
      }
    }
    if (st_mode == 2) { //Only works if st_mode is 2
      lcdSetText(uart1, 2, "Mode: DriveTurnL"); //Displays mode on LCD to avoid utter confusion from user.
      if(JSb7r == true) { //If 7R is pressed
        pivotLeftTimed(st_speed, st_time); //Turns left with whatever st_speed and st_time are set to.
      }
    }
    if (st_mode == 3) { //Only works if st_mode is 3
      lcdSetText(uart1, 2, "Mode: DriveTurnR"); //Displays mode on LCD to avoid utter confusion from user.
      if(JSb7r == true) { //If 7R is pressed
        pivotRightTimed(st_speed, st_time); //Turn right with whatever st_speed and st_time are set to.
      }
    }
    if (st_mode == 4) { //Only works if st_mode is 4
      lcdSetText(uart1, 2, "Mode: Mobile    "); //Displays mode on LCD to avoid utter confusion from user.
      if(JSb7r == true) { //If 7R is pressed
        setMobileTimed(st_speed, st_time); //Activates mobile goal pickup with whatever st_speed and st_time are set to.
      }
    }
    if (st_mode == 5) { //Only works if st_mode is 5
      lcdSetText(uart1, 2, "Mode: Claw      "); //Displays mode on LCD to avoid utter confusion from user.
      if(JSb7r == true) { //If 7R is pressed
        setClawTimed(st_speed, st_time); //Activates claw with whatever st_speed and st_time are set to.
      }
    }
    if (st_mode == 6) { //Only works if st_mode is 6
      lcdSetText(uart1, 2, "Mode: Tower     "); //Displays mode on LCD to avoid utter confusion from user.
      if(JSb7r == true) { //If 7R is pressed
        setTowerTimed(st_speed, st_time); //Activates tower with whatever st_speed and st_time are set to.
      }
    }
    if (st_mode > 6 || st_mode < 1) { //Constrains st_mode within the range of possible options
      st_mode = 1;
    }
  }

// Controls for Speedtest.
  if (speedtest == 1 && dev == 1) {
    if (JSb8u == true && JSb8d == false) { //When 8U is pressed, add 5 to speed value
      st_speed = st_speed+5;
      delay(250); //Buffer time for release (so it doesn't add 750 when you wanted 250)
    }
    if (JSb8d == true && JSb8u == false) { //When 8D is pressed, subtract 5 from the speed value
      st_speed = st_speed-5;
      delay(250); //Buffer time for release (so it doesn't add 750 when you wanted 250)
    }
    if (st_speed > 127 || st_speed < -127) { //Constrains st_speed within a specific range equal to the limits of the motors.
      st_speed = 0;
      delay(250); //Buffer time for release (so it doesn't add 750 when you wanted 250)
    }
    if (JSb8r == true && JSb8l == false) { //When 8R is pressed, add 100 to the time value
      st_time = st_time+50;
      delay(250); //Buffer time for release (so it doesn't add 750 when you wanted 250)
    }
    if (JSb8l == true && JSb8r == false) { //When 8L is pressed, subtract 100 from the time value
      st_time = st_time-50;
      delay(250); //Buffer time for release (so it doesn't add 750 when you wanted 250)
    }
  }
}
