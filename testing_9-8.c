#pragma config(Motor,  port2,           RightWheel1,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RightWheel2,   tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LeftWheel1,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LeftWheel2,    tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

//PRE-AUTON******************************************************************************************************************************************************************
void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

//AUTONOMOUS****************************************************************************************************************************************************************

task autonomous ()

{
	motor[RightWheel1] = 127;
	motor[RightWheel2] = 127;
	motor[LeftWheel1] = 127;
	motor[LeftWheel2] = 127;
	wait1Msec(300);
	motor[RightWheel1] = 0;
	motor[RightWheel2] = 0;
	motor[LeftWheel1] = 0;
	motor[LeftWheel2] = 0;
 wait1Msec(1200);

	AutonomousCodePlaceholderForTesting();
}

//USER CONTROL*************************************************************************************************************************************************************

task usercontrol()
{


	while (true)
	{

	  motor[RightWheel1] = vexRT[Ch1];
	  motor[RightWheel2] = vexRT[Ch1];
	  motor[LeftWheel1] = vexRT[Ch3];
	  motor[LeftWheel2] = vexRT[Ch3];

	  UserControlCodePlaceholderForTesting();
	}
}
