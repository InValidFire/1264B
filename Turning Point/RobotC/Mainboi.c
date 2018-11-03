#pragma config(Sensor, in1, PEPower, sensorAnalog)
#pragma config(Sensor, dgtl9, LedRed, sensorLEDtoVCC)
#pragma config(Sensor, dgtl10, LedYel, sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, LedGreen, sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, LedFull, sensorLEDtoVCC)
#pragma config(Motor, port1, ArmRight, tmotorVex393_HBridge, openLoop, driveRight)
#pragma config(Motor, port2, RightBack, tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor, port3, LeftBack, tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor, port4, BRightTower, tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor, port5, FRightTower, tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor, port6, FLeftTower, tmotorVex393_MC29, openLoop, reversed, driveLeft)
#pragma config(Motor, port7, BLeftTower, tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor, port8, RightFront, tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor, port9, LeftFront, tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor, port10, ArmLeft, tmotorVex393_HBridge, openLoop, reversed, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard!!*//

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VEX EDR                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This code is for the VEX cortex platform
#pragma platform(VEX2)

// Select Download method as "competition"
#pragma competitionControl(Competition)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
/*--------------------------------------------------------------------------------------------------//
//																																																  //
//		Credits:                                                                                      //
//		Drive-Control: Carmen Morgan                                                                  //
//		Autonomous: Logan Housden, Carmen Morgan, Jordan                                              //
//		Sensors: Logan Housden                                                                        //
//																																																  //
//--------------------------------------------------------------------------------------------------*/
#include "RecAndPlay.h" //Contains all modular components of the Record & Play system.

int autostart=0; //States whether or not autonomous has started
/* Possible states: autostart
0 = Autonomous off
1 = Autonomous has started
-1 = Autonomous is running in Debug mode
*/
int auto=0; //Determines selected autonomous; starts off disabled.
int autoselect; //Determines if we've selected LCD autonomous
int automin = 0; //Minimum value for LCD autonomous scrolling
int automax = 2; //Maximum value for LCD autonomous scrolling

int screen = 0; //Controls LCD display
float powerlevelCortex;
float powerlevelExpander;
float power; //Power Expander power level

float etime; //Expander time(used with batterylevel()
float ctime; //Cortex time(used with batterylevel()

int recordTime=15; //Length of time to record for (autonomous recording)
int recordWait=50; //Length of time to wait in between key logging. (in milliseconds)
bool recordMode = false; //Controls Autonomous Recording
bool debug = false; //Controls Debug toggle
bool debugoutput = false; //Output log statements to Debug Stream
int debugminutes;
int debugseconds;
int debugms;

int ledmode = 1; //Controls LED mode

// int count = 0; //For Record & Play
// Power Level
// Full = 1
// Good = .75
// OK   = .5
// Bad  = .25

//////////////

// ---------- Functions ---------- //
//function cap is 256, do not exceed this limit

//Record & Play -Jordan & Logan- //

//void recordAuto(char character) {
//	if (recordMode && debug) {
//		writeDebugStreamLine("autoString[%d] = '%c';",count ,character);
//		count++;
//	}
//}

//Autonomous Recording Function - Jordan
void recordAuto(char character) {
	if(recordMode && debug&&!debugoutput) {
		writeDebugStream("%c",character); //Used to print the recorded character in Record mode.
	}
}
//Battery Control Function - Carmen & Logan
void batterylevel(float desiredTime) { //cpwr = Cortex power, epwr = Expander power
	ctime=desiredTime*(1+(1-powerlevelCortex)); //AT=DT*(1+(1-BL)
	etime=desiredTime*(1+(1-powerlevelExpander));
}
//Movement Control Functions - Carmen & Logan
void move_pivot_turn(int time, int power) { //Right Turn in place (pos. power = left, neg. = right) ---> 90 degree turn
	batterylevel(time);
	motor[LeftFront] = power;
	motor[LeftBack] = power;
	motor[RightFront] = power*-1;
	motor[RightBack] = power*-1;
	wait1Msec(ctime*1000);
	motor[LeftFront] = 0;
	motor[LeftBack] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}
void move_swing_turn(int time, int lpower, int rpower) { //Adjustable Angle Turns (allows for swing turns by setting one value higher than the other)
	batterylevel(time);
	motor[LeftFront] = lpower;
	motor[LeftBack] = lpower;
	motor[RightFront] = rpower;
	motor[RightBack] = rpower;
	wait1Msec(etime*1000);
	motor[LeftFront] = 0;
	motor[LeftBack] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}

void move_straight(int time, int power) { //Move straight (positive for forward, negative for reverse)
	batterylevel(time);
	motor[LeftFront] = power;
	motor[LeftBack] = power;
	motor[RightFront] = power;
	motor[RightBack] = power;
	wait1Msec(etime*1000);
	motor[LeftFront] = 0;
	motor[LeftBack] = 0;
	motor[RightFront] = 0;
	motor[RightBack] = 0;
}
//Dab Function (Why Not?) - Carmen
void dab(int time, int power) {
	batterylevel(time);
	move_pivot_turn(etime*1000, power);
	move_pivot_turn(etime*1000, -power);
	move_swing_turn(etime*1000, power, power*-1);
}
//LED State Function - Logan (Idea: Jordan)
void led_state(int led1, int led2, int led3, int led4) { //Sets LEDs to specified value.
	/*
	| 0 = Off
	| 1 = On/Solid
	| 2 = On/Blink
	| 3 = Unchanged
	*/
	if(led1==0) { //Controls LedFull
		SensorValue[LedFull]=0;
		} else if(led1==1) {
		SensorValue[LedFull]=1;
		} else if(led1==2) {
		SensorValue[LedFull]=1;
		wait1Msec(500);
		SensorValue[LedFull]=0;
		wait1Msec(500);
		} else if(led1==3) {
	}

	if(led2==0) { //Controls LedGreen
		SensorValue[LedGreen]=0;
		} else if(led2==1) {
		SensorValue[LedGreen]=1;
		} else if(led2==2) {
		SensorValue[LedGreen]=1;
		wait1Msec(500);
		SensorValue[LedGreen]=0;
		wait1Msec(500);
		} else if(led2==3) {
	}

	if(led3==0) { //Controls LedYel
		SensorValue[LedYel]=0;
		} else if(led3==1) {
		SensorValue[LedYel]=1;
		} else if(led3==2) {
		SensorValue[LedYel]=1;
		wait1Msec(500);
		SensorValue[LedYel]=0;
		wait1Msec(500);
		} else if(led3==3) {
	}

	if(led4==0) { //Controls LedRed
		SensorValue[LedRed]=0;
		} else if(led4==1) {
		SensorValue[LedRed]=1;
		}else if(led4==2) {
		SensorValue[LedRed]=1;
		wait1Msec(500);
		SensorValue[LedRed]=0;
		wait1Msec(500);
		} else if(led4==3) {
	}
}
void moveLeft(int lpower) { //Drive control. If autonomous is started either in competition (1), or testing (-1), run for 50ms.
	if(autostart!=0) {
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous is running function: 'moveLeft'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
		motor[LeftFront] = lpower;
		motor[LeftBack] = lpower;
		wait1Msec(recordWait);
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous has finished function: 'moveLeft'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
	}
	if(autostart==0) {
		motor[LeftFront] = lpower;
		motor[LeftBack] = lpower;
	}
}
void moveRight(int rpower) {
	if(autostart!=0) {
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous is running function: 'moveRight'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
		motor[RightFront] = rpower;
		motor[RightBack] = rpower;
		wait1Msec(recordWait);
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous has finished function: 'moveRight'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
	}
	if(autostart==0) {
		motor[RightFront] = rpower;
		motor[RightBack] = rpower;
	}
}

void manipulatorTower(int power) { //Raise/Lower Arm Tower
	if(autostart!=0) {
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous is running function: 'manipulatorTower'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
		motor[FLeftTower] = power;
		motor[BLeftTower] = power;
		motor[BRightTower] = power;
		motor[FRightTower] = power;
		wait1Msec(recordWait);
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous has finished function: 'manipulatorTower'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
	}
	if(autostart==0) {
		motor[FLeftTower] = power;
		motor[BLeftTower] = power;
		motor[BRightTower] = power;
		motor[FRightTower] = power;
	}
}

void manipulatorArm(int power) { //Raise/Lower Arm
	if(autostart!=0) {
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous is running function: 'manipulatorArm'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
		motor[ArmLeft] = power;
		motor[ArmRight] = power;
		wait1Msec(recordWait);
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Autonomous has finished function: 'manipulatorArm'",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
	}
	if(autostart==0) {
		motor[ArmLeft] = power;
		motor[ArmRight] = power;
	}
}

//Autonomous Interpret Function - Jordan & Logan
//These are the interpreter functions, depending on the charater read, it will run the corresponding action.
void interpretMoveLeft(int num) { //possible bug - checks for each case on every letter, but will only find a matching case on one of every 4, potentially throwing off execution times
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Running function 'interpretMoveLeft'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	int i;
	for(i = 0; i < strlen(getAutoString(num)); i++) {
		switch(getAutoString(num)[i]) {
		case 'd':
			moveLeft(127);
			break;
		case 'e':
			moveLeft(-127);
			break;
		case 'h':
			moveLeft(0);
		}
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Finished function 'interpretMoveLeft'.",debugminutes,debugseconds,debugms);
			wait1Msec(1);
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]interpretMoveLeft ran '%d' many times",debugminutes,debugseconds,debugms,i);
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Finished function 'interpretMoveLeft'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
void interpretMoveRight(int num) {
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Running function 'interpretMoveRight'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	int i;
	for(i = 0; i < strlen(getAutoString(num)); i++) {
		switch(getAutoString(num)[i]) {
		case 'f':
			moveRight(127);
			break;
		case 'g':
			moveRight(-127);
			break;
		case 'l':
			moveRight(0);
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]interpretMoveRight ran '%d' many times",debugminutes,debugseconds,debugms,i);
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Finished function 'interpretMoveRight'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
void interpretManipulatorTower(int num) { //possible bug - checks for each case on every letter, but will only find a matching case on one of every 4, potentially throwing off execution times
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Running function 'interpretManipulatorTower'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	int i;
	for(i = 0; i < strlen(getAutoString(num)); i++) {
		switch(getAutoString(num)[i]) {
		case 'a':
			manipulatorTower(127);
			break;
		case 'b':
			manipulatorTower(-127);
			break;
		case 'c':
			manipulatorTower(0);
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]interpretManipulatorTower ran '%d' many times",debugminutes,debugseconds,debugms,i);
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Finished function 'interpretManipulatorTower'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}

/**
/ loop through each command in the AutoString then exit. - Mr. Spencer
*/
void interpretManipulatorArm(int num) { //possible bug - checks for each case on every letter, but will only find a matching case on one of every 4, potentially throwing off execution times
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Running function 'interpretManipulatorArm'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	int i;
	for(i = 0; i < strlen(getAutoString(num)); i++) {
		switch(getAutoString(num)[i]) {
		case 'i':
			manipulatorArm(30);
			break;
		case 'j':
			manipulatorArm(-90);
			break;
		case 'k':
			manipulatorArm(0);
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]interpretManipulatorArm ran '%d' many times",debugminutes,debugseconds,debugms,i);
		writeDebugStreamLine("[%dm:%ds:%dms] [A][F]Finished function 'interpretManipulatorArm'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
//Tasks// - Ensure that scheduler is the lowest user-created task
//These are the recording functions. When recording is on, it'll record the remote's actions to the debug log after a specified time interval.
task debugtimer {
	writeDebugStreamLine("[S][T] Task Started: 'debugtimer'");
	while(debugoutput) {
		debugminutes=time1[T4]/1000/60;
		debugseconds=time1[T4]/1000-(debugminutes*60);
		debugms=time1[T4]-(debugseconds*1000)-(debugminutes*60000);
		wait1Msec(1);
	}
	writeDebugStreamLine("[S][T] Task Ended: 'debugtimer'");
}
task recordMoveLeft {
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Started: 'recordMoveLeft'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	while(true) {
		if(autostart!=0) {
			interpretMoveLeft(auto);
			if(autostart==-1) {
				autostart=0;
			}
		}
		if(autostart==0&&debug) {
			if(vexRT[Ch3]>3) { //If Left-Joystick is positive send 'd' to log.
				wait1Msec(recordWait);
				if(vexRT[Ch3]>3) {
					recordAuto('d');
				}
				}else if(vexRT[Ch3]<-3) { //If Left-Joystick is negative send 'e' to log.
				wait1Msec(recordWait);
				if(vexRT[Ch3]<-3) {
					recordAuto('e');
				}
				}else if(vexRT[Ch3]>-3&&vexRT[Ch3]<3) { //If within deadzone, record nothing.
				wait1Msec(recordWait);
				if(vexRT[Ch3]>-3&&vexRT[Ch3]<3) {
					recordAuto('h');
				}
			}
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Ended: 'recordMoveLeft'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
task recordMoveRight {
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Started: 'recordMoveRight'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	while(true) {
		if(autostart!=0) {
			interpretMoveRight(auto);
			if(autostart==-1) {
				autostart=0;
			}
		}
		if(autostart==0&&debug) {
			if(vexRT[Ch2]>3) {
				wait1Msec(recordWait);
				if(vexRT[Ch2]>3) {
					recordAuto('f');
				}
				}else if(vexRT[Ch2]<-3) {
				wait1Msec(recordWait);
				if(vexRT[Ch2]<-3) {
					recordAuto('g');
				}
				}else if(vexRT[Ch2]<3&&vexRT[Ch2]>-3) {
				wait1Msec(recordWait);
				if(vexRT[Ch2]<3&&vexRT[Ch2]>-3) {
					recordAuto('l');
				}
			}
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Ended: 'recordMoveRight'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
task recordTower {
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Started: 'recordTower'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	while(true) {
		if(autostart!=0) {
			interpretManipulatorTower(auto);
			if(autostart==-1) {
				autostart=0;
			}
		}
		if(autostart==0&&debug) {
			if(vexRT[Btn6U]==1) {
				wait1Msec(recordWait);
				if(vexRT[Btn6D]==1) {
					recordAuto('a');
				}
				}else if(vexRT[Btn6D]==1) {
				wait1Msec(recordWait);
				if(vexRT[Btn6D]==1) {
					recordAuto('b');
				}
				} else if(vexRT[Btn6U]==0&&vexRT[Btn6D]==0) {
				wait1Msec(recordWait);
				if(vexRT[Btn6U]==0&&vexRT[Btn6D]==0) {
					recordAuto('c');
				}
			}
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Ended: 'recordTower'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
task recordArm {
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Started: 'recordArm'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	while(true) {
		if(autostart!=0) {
			interpretManipulatorArm(auto);
			if(autostart==-1) {
				autostart=0;
			}
		}
		if(autostart==0&&debug) {
			if(vexRT[Btn5D]==1) {
				wait1Msec(recordWait);
				if(vexRT[Btn5D]==1) {
					recordAuto('i');
				}
				} else if(vexRT[Btn5U]==1) {
				wait1Msec(recordWait);
				if(vexRT[Btn5U]==1) {
					recordAuto('j');
				}
				} else if(vexRT[Btn5U]==0&&vexRT[Btn5D]==0) {
				wait1Msec(recordWait);
				if(vexRT[Btn5U]==0&&vexRT[Btn5D]==0) {
					recordAuto('k');
				}
			}
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [R][T]Task Ended: 'recordArm'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
//Autonomous LED Control - Logan
task autoled { //Controls autonomous mode LED states
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [L][T]Task Started: 'autoled'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	ledmode=1;
	while(ledmode==1) {
		switch(auto) {
		case 0:
			led_state(1,0,0,1);
			break;
		case 1:
			led_state(1,0,0,0);
			break;
		case 2:
			led_state(0,1,0,0);
			break;
		case 3:
			led_state(0,0,1,0);
			break;
		case 4:
			led_state(0,0,0,1);
			break;
		case 5:
			led_state(2,0,0,0);
			break;
		case 6:
			led_state(0,2,0,0);
			break;
		case 7:
			led_state(0,0,2,0);
			break;
		case 8:
			led_state(0,0,0,2);
			break;
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [L][T]Task Ended: 'autoled'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
//Battery LED Control - Logan
task batteryled() { //Controls battery mode LED states & power level assignments (needs to be split into a constantly running task) (or merge LED tasks into one)
	ledmode=-1; //Used to switch between LED modes with the Debug mode on LCD
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [L][T]Task Started: 'batteryled'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	while(ledmode==-1) {
		power=SensorValue[PEPower]/280.0;
		if(nImmediateBatteryLevel/1000.0>=8.5 && power>=8.5) { //Both full, blink LedFull
			while(true) {
				powerlevelCortex=1;
				powerlevelExpander=1;
				led_state(2,0,0,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.5 && power>=8.0){ //Cortex full, PE good; solid Full, blink Green.
			while(true) {
				powerlevelCortex=1;
				powerlevelExpander=0.75;
				led_state(1,2,0,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.5 && power>=7.5) { //Cortex Full, PE OK; Solid Full, blink Yel
			while(true) {
				powerlevelCortex=1;
				powerlevelExpander=0.5;
				led_state(1,0,2,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.5 && power<7.5) { //Cortex Full, PE Bad; Solid Full, Blink Red
			while(true) {
				powerlevelCortex=1;
				powerlevelExpander=0.25;
				led_state(1,0,0,2);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.0 && power>=8.5) { //Cortex Good, PE Full; Solid Green, Blink Full
			while(true) {
				powerlevelCortex=0.75;
				powerlevelExpander=1;
				led_state(2,1,0,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.0 && power>=8.0) { //Cortex Good, PE Good; Blink Green
			while(true) {
				powerlevelCortex=0.75;
				powerlevelExpander=0.75;
				led_state(0,2,0,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.0 && power>=7.5) { //Cortex Good, PE OK; Solid Green, Blink Yel
			while(true) {
				powerlevelCortex=0.75;
				powerlevelExpander=0.5;
				led_state(0,1,2,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=8.0 && power<7.5) { //Cortex Good, PE Bad; Solid Green, Blink Red
			while(true) {
				powerlevelCortex=0.75;
				powerlevelExpander=0.25;
				led_state(0,1,0,2);
			}
			} else if(nImmediateBatteryLevel/1000.0>=7.5 && power>=8.5) { //Cortex OK, PE Full; Solid Yel, Bink Full
			while(true) {
				powerlevelCortex=0.5;
				powerlevelExpander=1;
				led_state(2,0,1,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=7.5 && power>=8.0) { //Cortex OK, PE Good; Solid Yel, Blink Green
			while(true) {
				powerlevelCortex=0.5;
				powerlevelExpander=0.75;
				led_state(0,2,1,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=7.5 && power>=7.5) { //Cortex OK, PE OK; Blink Yel
			while(true) {
				powerlevelCortex=0.5;
				powerlevelExpander=0.5;
				led_state(0,0,2,0);
			}
			} else if(nImmediateBatteryLevel/1000.0>=7.5 && power<7.5) { //Cortex OK, PE Bad; Solid Yel, Blink Red
			while(true) {
				powerlevelCortex=0.5;
				powerlevelExpander=0.25;
				led_state(0,0,1,2);
			}
			} else if(nImmediateBatteryLevel/1000.0<7.5 && power>=8.5) { //Cortex Bad, PE Full; Solid Red, Blink Full
			while(true) {
				powerlevelCortex=0.25;
				powerlevelExpander=1;
				led_state(2,0,0,1);
			}
			} else if(nImmediateBatteryLevel/1000.0<7.5 && power>=8.0) { //Cortex Bad, PE Good; Solid Red, Blink Green
			while(true) {
				powerlevelCortex=0.25;
				powerlevelExpander=0.75;
				led_state(0,2,0,1);
			}
			} else if(nImmediateBatteryLevel/1000.0<7.5 && power>=7.5) { //Cortex Bad, PE OK; Solid Red, Blink Yel
			while(true) {
				powerlevelCortex=0.25;
				powerlevelExpander=0.5;
				led_state(0,0,2,1);
			}
			} else if(nImmediateBatteryLevel/1000.0<7.5 && power<7.5) { //Cortex Bad, PE Bad; Blink Red
			while(true) {
				powerlevelCortex=0.25;
				powerlevelExpander=0.25;
				led_state(0,0,0,2);
			}
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [L][T]Task Ended: 'batteryled'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
//LCD Task & Debug Mode - Logan
int	mainLoopCounter=0;
int	debugLoopCounter=0;
task lcd { //For LCD Autonomous Selection
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [D][T]Task Started: 'lcd'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	int leftbutton = 1; //aliases for button numbers on LCD
	int centerbutton = 2;
	int rightbutton = 4;
	int leftright = 5;
	int battery = 1;
	bool debugRecordStart = false; //Used to initialize the recordAuto tasks in Debug mode only.
	int motornum=0;
	int motornummin=0;
	int motornummax=10;
	char motorpower[50];
	mainLoopCounter=0;
	debugLoopCounter=0;
	while(true) {
		mainLoopCounter++;
		while(debug) { //Debug mode
			debugLoopCounter++;
			int screenmin = 0;
			int screenmax = 5;
			if(!debugRecordStart&&screen==4) {
				startTask(recordMoveLeft);
				startTask(recordMoveRight);
				startTask(recordTower);
				startTask(recordArm);
				debugRecordStart=true;
			}
			if(debugRecordStart&&screen!=4) {
				stopTask(recordMoveLeft);
				stopTask(recordMoveRight);
				stopTask(recordTower);
				stopTask(recordArm);
				debugRecordStart=false;
			}
			if(nLCDButtons==leftright&&screen==0) {
				debug=false;
				wait1Msec(250);
			}
			if(nLCDButtons==leftbutton) { //Scrolling controls
				if(screen>screenmin) {
					screen--;
					clearLCDLine(0);
					clearLCDLine(1);
					wait1Msec(250);
					} else {
					screen=screenmax;
					clearLCDLine(0);
					clearLCDLine(1);
					wait1Msec(250);
				}
			}
			if(nLCDButtons==rightbutton) { //More Scrolling Controls
				if(screen<screenmax) {
					screen++;
					clearLCDLine(0);
					clearLCDLine(1);
					wait1Msec(250);
					} else {
					screen=screenmin;
					clearLCDLine(0);
					clearLCDLine(1);
					wait1Msec(250);
				}
			}
			switch(screen) {
			case 0: //Lets user know Debug is on.
				displayLCDCenteredString(0,"Debug");
				displayLCDCenteredString(1,"Mode");
				break;
			case 1: //Displays battery voltages
				char batteryvoltage[50];
				if(nLCDButtons==centerbutton) {
					battery=battery*-1;
				}
				switch(battery) { //Lets user see Cortex || Expander power levels
				case 1:
					sprintf(batteryvoltage, "%1.2f%c", nImmediateBatteryLevel/1000.0);
					displayLCDCenteredString(0,"Cortex");
					displayLCDCenteredString(1,batteryvoltage);
					wait1Msec(250);
					break;
				case -1:
					displayLCDCenteredString(0,"Expander");
					sprintf(batteryvoltage, "%1.2f%c", power/280.0);
					displayLCDCenteredString(1,batteryvoltage);
					wait1Msec(250);
					break;
				}
				break;
			case 2: //Autonomous Testing Screen
				char autotime[5];
				if(autostart==0) { //When first going into screen, display prompt.
					displayLCDCenteredString(0,"Run Autonomous?");
				}
				if(nLCDButtons==centerbutton&&autostart!=-1) { //When center buttom pressed, initialize autonomous.
					if(debugoutput) {
						writeDebugStreamLine("[%dm:%ds:%dms] [D][T]Task 'lcd' setting autostart to -1",debugminutes,debugseconds,debugms);
						wait1Msec(1);
					}
					autostart = -1;
					clearTimer(T1);
					if(debugoutput) {
						writeDebugStreamLine("[%dm:%ds:%dms] [D][T]Task 'lcd starting task: 'autonomous'",debugminutes,debugseconds,debugms);
						wait1Msec(1);
					}
					startTask(autonomous);
				}
				if(autostart==-1) { //Displays timer while autonomous (testing) is running)
					sprintf(autotime,"%2.2f",time1[T1]/1000.0);
					displayLCDCenteredString(0,"Running!");
					displayLCDCenteredString(1,autotime);
				}
				displayLCDCenteredString(1,autotime);
				break;
			case 3:
				displayLCDCenteredString(0,"LED Mode");
				if(ledmode==-1) {
					displayLCDCenteredString(1,"Battery");
					} else if(ledmode==1) {
					displayLCDCenteredString(1,"Autonomous");
				}
				if(nLCDButtons==centerbutton) {
					ledmode=ledmode*-1;
					switch(ledmode) {
					case 1:
						stopTask(batteryled);
						startTask(autoled);
						break;
					case -1:
						stopTask(autoled);
						startTask(batteryled);
						break;
					}
					wait1Msec(250);
				}
				break;
			case 4:
				char timerRecord[6];
				if(!recordMode) {
					displayLCDCenteredString(0,"Record Off");
				}
				if(recordMode) {
					displayLCDCenteredString(0,"Record On");
					sprintf(timerRecord,"%3.2f",time1[T3]/1000.0);
					displayLCDCenteredString(1,timerRecord);
				}
				if(nLCDButtons==centerbutton&&!recordMode) {
					recordMode=true;
					clearTimer(T3);
					wait1Msec(250);
				}
				if(nLCDButtons==centerbutton&&recordMode) {
					recordMode=false;
					wait1Msec(250);
				}
				if(time1[T3]/1000.0>recordTime) {
					recordMode=false;
				}
				break;
			case 5:
				if(nLCDButtons==centerbutton) { //This switches the motornum variable on a press of the center button, used by the switch statement below.
					if(motornum<motornummax) {
						motornum++;
						wait1Msec(250);
						} else {
						motornum=motornummin;
						wait1Msec(250);
					}
				}
				switch(motornum) { //This system controls which Motor's power is displayed.
				case 0:
					displayLCDCenteredString(0,"Motor Power");
					displayLCDCenteredString(1,"");
					break;
				case 1:
					sprintf(motorpower,"%d",motor[LeftFront]); //Gotta figure out how to convert motor to string.
					displayLCDCenteredString(0,"LeftFront");
					displayLCDCenteredString(1,motorpower);
					break;
				case 2:
					sprintf(motorpower,"%d",motor[LeftBack]);
					displayLCDCenteredString(0,"LeftBack");
					displayLCDCenteredString(1,motorpower);
					break;
				case 3:
					sprintf(motorpower,"%d",motor[RightFront]);
					displayLCDCenteredString(0,"RightFront");
					displayLCDCenteredString(1,motorpower);
					break;
				case 4:
					sprintf(motorpower,"%d",motor[RightBack]);
					displayLCDCenteredString(0,"RightBack");
					displayLCDCenteredString(1,motorpower);
					break;
				case 5:
					sprintf(motorpower,"%d",motor[FLeftTower]);
					displayLCDCenteredString(0,"FLeftTower");
					displayLCDCenteredString(1,motorpower);
					break;
				case 6:
					sprintf(motorpower,"%d",motor[BLeftTower]);
					displayLCDCenteredString(0,"BLeftTower");
					displayLCDCenteredString(1,motorpower);
					break;
				case 7:
					sprintf(motorpower,"%d",motor[FRightTower]);
					displayLCDCenteredString(0,"FRightTower");
					displayLCDCenteredString(1,motorpower);
					break;
				case 8:
					sprintf(motorpower,"%d",motor[BRightTower]);
					displayLCDCenteredString(0,"BRightTower");
					displayLCDCenteredString(1,motorpower);
					break;
				case 9:
					sprintf(motorpower,"%d",motor[ArmLeft]);
					displayLCDCenteredString(0,"ArmLeft");
					displayLCDCenteredString(1,motorpower);
					break;
				case 10:
					sprintf(motorpower,"%d",motor[ArmRight]);
					displayLCDCenteredString(0,"ArmRight");
					displayLCDCenteredString(1,motorpower);
					break;
				}
			}
		}
		while(debug==false) {
			if(debugRecordStart) {
				debugRecordStart=false;
			}
			if(nLCDButtons==leftright) {
				debug=true;
				wait1Msec(250);
			}
			if(nLCDButtons==leftbutton) { //Scrolling controls
				if(auto>automin) { //If auto is greater than the minimum, subtract one, otherwise, go to max.
					auto--;
					wait1Msec(250);
					} else {
					auto=automax;
				}	//hi
			}
			if(nLCDButtons==rightbutton) { //More Scrolling Controls
				if(auto<automax) { //If auto is less than the max, add one, otherwise, go to min
					auto++;
					wait1Msec(250);
					} else {
					auto=automin;
				}
			}
			if(nLCDButtons==centerbutton) { //Lock-in selected autonomous and end the task (see task schedule)
				autoselect=1;
			}
			switch(auto) { //Sets the LCD to display the name of selected Autonomous and set the LEDs
			case 0:
				if(autoselect==1) {
					displayLCDCenteredString(0,"Selected");
					} else if(autoselect==0) {
					displayLCDCenteredString(0,"");
				}
				displayLCDCenteredString(1, "Auto Off");
				wait1Msec(100); //These waits keep the LCD from hogging up the Cortex CPU.
				break;
			case 1:
				if(autoselect==1) {
					displayLCDCenteredString(0,"Selected");
					} else if(autoselect==0) {
					displayLCDCenteredString(0,"");
				}
				displayLCDCenteredString(1, "Auto 1");
				wait1Msec(100);
				break;
			case 2:
				if(autoselect==1) {
					displayLCDCenteredString(0,"Selected");
					} else if(autoselect==0) {
					displayLCDCenteredString(0,"");
				}
				displayLCDCenteredString(1, "Auto 2");
				wait1Msec(100);
				break;
			}
		}
	}
}
// Task Schedule - Logan
task scheduler { //Schedules the startup of the bot and user-created tasks
	if(debugoutput) {
		startTask(debugtimer);
		writeDebugStreamLine("[%dm:%ds:%dms] [S][T]Task Started: 'scheduler'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	bLCDBacklight = true;
	startTask(autoled);
	startTask(lcd); //Starts with allowing us to select the autonomous with LCD
	waitUntil(autoselect==1||autostart==1);
	stopTask(lcd);
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [S][T]Task 'scheduler' stopped task 'lcd'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	stopTask(autoled);
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [S][T]Task 'scheduler' stopped tasl 'autoled'",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	startTask(batteryled);
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [S][T]Task Ended: 'scheduler'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
/////////

//Autonomous// - Keeping pre_auton function nearby for sanity reasons.
void pre_auton()
{
	bStopTasksBetweenModes = false;
	clearTimer(T4); //This timer is to be used for Debug statements only
	startTask(scheduler);
}
//Autonomous - Logan
task autonomous()
{
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][T]Task Started: 'autonomous'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	if(debug==false) {
		autostart=1;
	}
	switch(auto) { //Runs different autonomous based on the value of 'auto'
	case 0: //This is if we want to disable autonomous; when auto == 0, do nothing.
		if(autostart==-1) {
			autostart=0;
		}
		break;
	case 1:
		prepAutoString(1); //Bug - When running the autonomous multiple times under the same boot, this runs more than once, adding more to the Autonomous string.
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][S]Prepped Autonomous String");
			wait1Msec(1);
		}
		startTask(recordArm);
		if(debugoutput) {
			writeDebugStreamLine("[%dm:%ds:%dms] [A][S]Started playback functions w/ Autonomous");
			wait1Msec(1);
		}
		break;
	case 2:
		startTask(recordArm);
		if(autostart==-1) {
			autostart=0;
		}
		break;
	}
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [A][T]Task Ended: 'autonomous'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
}
////////////////////////

//User Control// - Please don't be stupid(like me) and make sure that everything control-related is in the while() loop.
// - Logan & Carmen
task usercontrol() {
	if(debugoutput) {
		writeDebugStreamLine("[%dm:%ds:%dms] [U][T]Task Started: 'usercontrol'.",debugminutes,debugseconds,debugms);
		wait1Msec(1);
	}
	while (true) {
		if(!debug) { //Normal Controls when not in Debug mode.
			moveLeft(vexRT[Ch3]); //LeftDrive controls
			moveRight(vexRT[Ch2]); //RightDrive controls
			//Tower controls
			if(vexRT[Btn6U] == 1) { //Tower one controls (left from front)
				manipulatorTower(127);
				} else if(vexRT[Btn6D] == 1) { //Tower two controls (right from front)
				manipulatorTower(-127);
				} else { //Stop towers if nothing is pressed
				manipulatorTower(0);
			}

			//Arm controls
			if(vexRT[Btn5D] == 1) {
				manipulatorArm(30);
				} else if(vexRT[Btn5U] == 1) {//Extend Outwards
				manipulatorArm(-90);
				}	else{ //Stop arms if nothing is pressed
				manipulatorArm(0);
			}
		}

		if(debug) { //Conditional Controls for Debug Mode.
			if(screen==4) {//RecordAuto controls
				if(recordTime>time1[T3]/1000.0) {
					moveLeft(vexRT[Ch3]); //LeftDrive controls
					moveRight(vexRT[Ch2]); //RightDrive controls
					//Tower controls
					if(vexRT[Btn6U] == 1) { //Tower one controls (left from front)
						manipulatorTower(127);
						} else if(vexRT[Btn6D] == 1) { //Tower two controls (right from front)
						manipulatorTower(-127);
						} else { //Stop towers if nothing is pressed
						manipulatorTower(0);
					}
					//Arm controls
					if(vexRT[Btn5D] == 1) {
						manipulatorArm(30);
						} else if(vexRT[Btn5U] == 1) {//Extend Outwards
						manipulatorArm(-90);
						}	else{ //Stop arms if nothing is pressed
						manipulatorArm(0);
					}
				}
				if(recordTime<time1[T3]/1000.0) {
					allMotorsOff();
				}
			}
		}
	}
	if(debugoutput) {
		writeDebugStreamLine("[U][T]Task Ended: 'usercontrol'.");
		wait1Msec(1);
	}
}
