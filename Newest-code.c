#pragma config(Sensor, dgtl1,  EncoX2Y1,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  EncoX2Y2,       sensorQuadEncoder)
#pragma config(Motor,  port1,           X1Y1,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           Arm1U,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Arm1D,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           X2Y2,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           Arm2D,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           X2Y1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           Claw2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Claw1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Arm2U,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          X1Y2,          tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//moverobot(sydeways, rotate, firword/back, 0, aut or not, speed for auto)

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



//PRE_AUTON------------------------------------------------------------------------
void pre_auton()
{

	bStopTasksBetweenModes = true;

}
//functions-------------------------------------------------------------------------

void drive (float dist, float angle, float speed)
{
	float c=3.25*PI;//finds circumfrence
	float rn=dist/c;//finds rotations needed
	SensorValue[EncoX2Y1] = 0;//sets encoder to zero
	SensorValue[EncoX2Y2] = 0;//sets encoder to zero
	float ra=0;//gives variable for motor X2Y2 rotations
	float rb=0;//gives variable for motor X2Y1 rotations
	float vCh1=sinDegrees(angle)*speed;//     ^
	float vCh2=cosDegrees(angle)*speed;//     ^
	float vCh3=cosDegrees(angle)*speed*0.8354;//     ^
	float vCh4=sinDegrees(angle)*speed;//<--- ^this and above gives vaiables for motors based on direction of joystick
	while (sqrt(ra*ra+rb*rb)<rn)//formula for part of pathagorean theorem
	{

	  motor[X2Y1] = vCh3+vCh4;
		motor[X1Y1] = vCh3-vCh4;
		motor[X2Y2] = vCh2-vCh1;
		motor[X1Y2] = vCh2+vCh1;
		ra=SensorValue[EncoX2Y2]/90.0;
		rb=SensorValue[EncoX2Y1]/90.0;

	}
	motor[X1Y1] = 0;
	motor[X1Y2] = 0;
	motor[X2Y1] = 0;
	motor[X2Y2] = 0;
}

void turnlef90 ()
{
	SensorValue[EncoX2Y1] = 0;
	while(true)
	{
		if(SensorValue[EncoX2Y1] < 150)
		{
	  	motor[X2Y1] = -100;
	  	motor[X1Y1] = -100;
	  	motor[X2Y2] = 100;
	  	motor[X1Y2] = 100;
	  }
	  else if(SensorValue[EncoX2Y1] > 155)
	  {
	  	motor[X2Y1] = 100;
	  	motor[X1Y1] = 100;
	  	motor[X1Y2] = -100;
	  	motor[X2Y2] = -100;
	  }
	  else
	  {
	  	motor[X2Y1] = 0;
	  	motor[X1Y1] = 0;
	  	motor[X1Y2] = 0;
	  	motor[X2Y2] = 0;
	  	break;
	  }
}
/* SOME THINGS TO CONSIDER:

1) ARC LENGTH:
	C_WHEEL =<WHEEL DIAMETER>*PI
	C_ROBOT = <ROBOT DIAMETER>*PI
	ROTATIONS_NEEDED = C_ROBOT * (<ANGLE TO TURN>/360) / C_WHEEL

2) PROPORTIONAL CONTROL:
	WHILE ROTATIONS < ROTATIONS_NEEDED-0.1 OR ROTATIONS > ROTATIONS_NEEDED+0.1
		IF ROTATIONS_NEEDED-ROTATIONS < 1
			MOTOR_SPEED = 10*(ROTATIONS_NEEDED-ROTATIONS)
		ELSE
			MOTOR_SPEED = SPEED
	TURN OFF MOTOR*/
}


void stopmotors ()
{
	motor[Arm1U] = 0;
	motor[Arm2U] = 0;
	motor[Arm2D] = 0;
	motor[Arm1D] = 0;
	motor[Claw1] = 0;
	motor[Claw2] = 0;
	motor[X1Y1] = 0;
	motor[X1Y2] = 0;
	motor[X2Y1] = 0;
	motor[X2Y2] = 0;
}

void raisearmfull ()
{
	motor[Arm1U] = 120;
	motor[Arm2U] = 120;
	motor[Arm2D] = 120;
	motor[Arm1D] = 120;
	wait1Msec(1000);
}

void openclaw ()
{
	motor[Claw1] = 120;
	motor[Claw2] = 120;
	wait1Msec(200);
	motor[Claw1] = 0;
	motor[Claw2] = 0;

}

void doauton ()
{
	openclaw ();
	wait1Msec(1000);
  raisearmfull ();
  motor[Claw1] = -127;
  motor[Claw2] = -127;
  wait1Msec(100);
  motor[Claw1] = 0;
  motor[Claw2] = 0;
  wait1Msec(200);
  motor[Claw1] = 127;
  motor[Claw2] = 127;
  wait1Msec(100);
  motor[Claw1] = 0;
  motor[Claw2] = 0;
  motor[Arm1D] = 127;
  motor[Arm1U] = 127;
  motor[Arm2D] = 127;
  motor[Arm2U] = 127;
  wait1Msec(200);
  motor[Arm1D] = 0;
  motor[Arm1U] = 0;
  motor[Arm2D] = 0;
  motor[Arm2U] = 0;
  drive (250,0, 127);
  drive(30, 180, 127);
}



//AUTONOMOUS-------------------------------------------------------------------------

task autonomous()
{
	doauton ();

	AutonomousCodePlaceholderForTesting();
}
//USERCONTROL-----------------------------------------------------------------------

task usercontrol()
{
    while (true)
  {

		motor[Arm1D] = vexRT[Ch2Xmtr2];
		motor[Arm2D] = vexRT[Ch2Xmtr2];
		motor[Arm1U] = vexRT[Ch2Xmtr2];
		motor[Arm2U] = vexRT[Ch2Xmtr2];
		motor[Claw1] = vexRT[Ch4Xmtr2];
		motor[Claw2] = vexRT[Ch4Xmtr2];
	  motor[X2Y1] = vexRT[Ch3]+vexRT[Ch4];
		motor[X1Y1] = vexRT[Ch3]-vexRT[Ch4];
		motor[X2Y2] = vexRT[Ch2]-vexRT[Ch1];
		motor[X1Y2] = vexRT[Ch2]+vexRT[Ch1];

		if(vexRT[Btn7U] == 1)
	  {
	  	doauton();
		}

		if(vexRT[Btn5U] == 1)
		{
			stopmotors();
		}
	}
}
