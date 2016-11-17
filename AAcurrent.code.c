#pragma config(Sensor, in1,    PotenR,         sensorPotentiometer)
#pragma config(Sensor, in2,    PotenB,         sensorPotentiometer)
#pragma config(Sensor, dgtl2,  UltS1,          sensorSONAR_cm)
#pragma config(Sensor, dgtl4,  UltS2,          sensorSONAR_cm)
#pragma config(Sensor, dgtl6,  UltS3,          sensorSONAR_cm)
#pragma config(Sensor, dgtl8,  EncoR1,         sensorQuadEncoder)
#pragma config(Sensor, dgtl10, EncoL1,         sensorQuadEncoder)
#pragma config(Motor,  port1,           LeftWheel2,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port3,           Shoulder1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           Shoulder2,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Elbow,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          RightWheel2,   tmotorVex393_HBridge, openLoop)
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
//my functions

void turn90right ()
{
	SensorValue[EncoR1] = 0;

	while(SensorValue(EncoR1) < 225)
	{
		motor[RightWheel2] = -90;
		motor[LeftWheel2] = 90;
	}

}

void turn90left ()
{
	SensorValue[EncoL1] = 0;

	while(SensorValue(EncoL1) > -250)
	{
		motor[RightWheel2] = 90;
		motor[LeftWheel2] = -90;
	}
}

void moveforward (int cm)
{
	while(SensorValue[UltS1] < cm)
	{
		motor[RightWheel2] = 63;
		motor[LeftWheel2] = 63;
	}
	motor[RightWheel2] = 0;
	motor[LeftWheel2] = 0;
}

void movebackward (int cm)
{
	while(SensorValue[UltS1] > cm)
	{
		motor[RightWheel2] = -63;
		motor[LeftWheel2] = -63;
	}
	motor[RightWheel2] = 0;
	motor[LeftWheel2] = 0;
}

void flipstar ()
{
	while(SensorValue[PotenR] < 3880)
	{
		motor[Shoulder1] = 150;
		motor[Shoulder2] = 150;
		motor[Elbow] = 0;
	}
	motor[Shoulder1] = 0;
	motor[Shoulder2] = 0;

	while(SensorValue[PotenB] < 4095)
	{
		motor[Elbow] = 90;
	}
	motor[Elbow] = 0;

	while(SensorValue[PotenB] > 4095)
	{
		motor[Elbow] = -90;
	}
	motor[Elbow] = 0;
}


//AUTONOMOUS****************************************************************************************************************************************************************

void doAutonomous()
{
	moveforward(46);
	moveforward(46);
	turn90right();
	movebackward(33.02);
	turn90left();
	moveforward(46+80);
	moveforward(46+80);
	movebackward(46);
	motor[Elbow] = -127;
	wait1Msec(1200);
	motor[Elbow] = 0;
	motor[Elbow] = 127;
	wait1Msec(400);
	motor[Elbow] = 0;
	moveforward(46+80);
	moveforward(46+80);
	movebackward(46);
	motor[Elbow] = 0;
	wait1Msec(500);
	moveforward(46+70);
//	flipstar();


}


task autonomous ()
{
	doAutonomous();
}

//USER CONTROL*************************************************************************************************************************************************************

task usercontrol()
{


	while (1==1)
	{



		motor[RightWheel2] = vexRT[Ch2];//drives le right wheel

	  motor[LeftWheel2] = vexRT[Ch3];//drives le left wheel

	  motor[Shoulder1] = vexRT[Ch3Xmtr2];//controls Shoulder joint
		motor[Shoulder2] = vexRT[Ch3Xmtr2];//controls Shoulder joint

	  motor[Elbow] = vexRT[Ch2Xmtr2];//controls elbow joint

	  if(vexRT[Btn5D] == 1)
	  {
	  	doAutonomous();
		}

		if(vexRT[Btn5UXmtr2] == 1)
		{
			flipstar();
		}
	}
}
