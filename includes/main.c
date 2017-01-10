//add to main
//#pragma config(UART_Usage, UART1, uartVEXLCD, baudRate19200, IOPins, None, None)
//#pragma config(Sensor, in8,    gyro,           sensorGyro)
//#pragma config(Sensor, dgtl1,  RedOrBlue,      sensorDigitalIn)
//#pragma config(Sensor, dgtl2,  LeftOrNot,      sensorDigitalIn)
//#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed, driveRight)
//#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop, reversed, driveRight)
//#pragma config(Motor,  port8,           frontLeft,     tmotorVex393_MC29, openLoop, driveLeft)
//#pragma config(Motor,  port9,           backLeft,      tmotorVex393_MC29, openLoop, driveLeft)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//add to main


////put in pre-atun
//	//reset incoders
//	//nMotorEncoder[RightShootE]=0;
//	//reset gyro
//	SensorType[gyro] = 0;
//	wait1Msec(50);
//	SensorType[gyro] = sensorGyro;
//	wait1Msec(1300);
//	//angle is in degrees - multiplying by 10 done in the turn function
//	//Adjust SensorFullCount to set the "rollover" point. A value of 3600 sets the rollover point to +/-3600
//	SensorFullCount[gyro] = 7200;
////end pre-atun


//88888888888888888888888888888 stop motors 8888888888888888888888888888888888
void stopmotors()
{
	motor[frontRight] = 0;
	motor[backRight]  = 0;
	motor[frontLeft]  = 0;
	motor[backLeft]   = 0;
	wait1Msec(10);
}
void moverobot(int xx1, int xx2, int yy1, int duration, int automode, int gospeed)
{
	int direction;
	int delta = 35;
	if (automode==0)
	{
		motor[frontRight] = yy1 - xx2 - xx1;
		motor[backRight]  =  yy1 - xx2 + xx1;
		motor[frontLeft]  = yy1 + xx2 + xx1;
		motor[backLeft]   =  yy1 + xx2 - xx1;
		wait1Msec(duration);

	}
	//This section is for automous mode movement of the base
	if (automode==1)
	{
		if(yy1!=0)//code for movement forward or reverse.  +yy1=forward, -yy1=reverse
		{
			if (yy1>0) direction=1;
			else if (yy1<0) direction=-1;
			//writeDebugStream("yy1= %d", yy1);  // writes the current value of int 'yy1' to the debug stream
			SensorValue[backLeftE]  = 0;
			SensorValue[backRightE] = 0;
			// this while loop moves the base until the desired distance - yy1 - is achieved
			while ((abs(SensorValue[backLeftE]) < (abs(yy1)-30)) || (abs(SensorValue[backRightE])<(abs(yy1)-30)))
				//  || ((nMotorEncoder[backLeft]>yy1+200)&&(-nMotorEncoder[backRight]>yy1+200)))
			{
				if (abs(SensorValue[backLeftE]) == abs(SensorValue[backRightE]))
				{
					motor[frontRight] = gospeed*direction;
					motor[backRight]  = gospeed*direction;
					motor[frontLeft]  = gospeed*direction;
					motor[backLeft]   = gospeed*direction;
					wait1Msec(1);
				}
				//if moving forward and left leads, slow down left side
				else if ((abs(SensorValue[backLeftE]) > abs(SensorValue[backRightE])) && (direction==1))
				{
					motor[frontRight] = gospeed;
					motor[backRight]  = gospeed;
					motor[frontLeft]  = (gospeed-delta);
					motor[backLeft]   = (gospeed-delta);
					wait1Msec(1);
				}
				//if moving backward and left leads, slow down left side
				else if ((abs(SensorValue[backLeftE]) > abs(SensorValue[backRightE])) && (direction==-1))
				{
					motor[frontRight] = -gospeed;
					motor[backRight]  = -gospeed;
					motor[frontLeft]  = -(gospeed-delta);
					motor[backLeft]   = -(gospeed-delta);
					wait1Msec(1);
				}
				//if moving forward and left lags, slow down right side
				else if ((abs(SensorValue[backLeftE]) < abs(SensorValue[backRightE])) && (direction==1))
				{
					motor[frontRight] =  (gospeed-delta);
					motor[backRight]  =  (gospeed-delta);
					motor[frontLeft]  =  gospeed;
					motor[backLeft]   =  gospeed;
					wait1Msec(1);
				}
				//if moving backward and left lags, slow down right side
				else if ((abs(SensorValue[backLeftE]) < abs(SensorValue[backRightE])) && (direction==-1))
				{
					motor[frontRight] = -(gospeed-delta);
					motor[backRight]  = -(gospeed-delta);
					motor[frontLeft]  = -gospeed;
					motor[backLeft]   = -gospeed;
					wait1Msec(1);
				}
				else stopmotors();
			}
			stopmotors();
		}
		if(xx1!=0)//code for movement left or right.  +xx1=right, -xx1=left
		{
			if (xx1>0) direction=1;
			if (xx1<0) direction=-1;

			SensorValue[backLeftE]  = 0;
			SensorValue[frontLeftE] = 0;

			while (( abs(SensorValue[backLeftE]) < (abs(xx1)-30))&&(abs(SensorValue[frontLeftE]) < (abs(xx1)-30)))
				//||((abs(nMotorEncoder[backLeft]) > abs(xx1+200)) && abs(nMotorEncoder[frontLeft]) > abs(xx1+200)))
			{
				//move right equally
				if (abs(SensorValue[backLeftE]) == abs(SensorValue[frontLeftE]))
				{
					motor[frontRight] = -gospeed*direction;
					motor[backRight]  = gospeed*direction;
					motor[frontLeft]  = gospeed*direction;
					motor[backLeft]   = -gospeed*direction;
					wait1Msec(1);
				}
				//if moving right and back leads, slow down back motors
				else if ((abs(SensorValue[backLeftE]) > abs(SensorValue[frontLeftE])) && (direction==1))
				{
					motor[frontRight] = -gospeed;
					motor[backRight]  = (gospeed-delta);
					motor[frontLeft]  = gospeed;
					motor[backLeft]   = -(gospeed-delta);
					wait1Msec(1);
				}
				//if moving left and back leads, slow down back motors
				else if ((abs(SensorValue[backLeftE]) > abs(SensorValue[frontLeftE])) && (direction==-1))
				{
					motor[frontRight] = gospeed;
					motor[backRight]  = -(gospeed-delta);
					motor[frontLeft]  = -gospeed;
					motor[backLeft]   = (gospeed-delta);
					wait1Msec(1);
				}
				//if moving right and front leads, slow down front motors
				else if ((abs(SensorValue[backLeftE]) < abs(SensorValue[frontLeftE])) && (direction==1))
				{
					motor[frontRight] =  -(gospeed-delta);
					motor[backRight]  =  gospeed;
					motor[frontLeft]  =  (gospeed-delta);
					motor[backLeft]   =  -gospeed;
					wait1Msec(1);
				}
				//if moving left and front leads, slow down front motors
				else if ((abs(SensorValue[backLeftE]) < abs(SensorValue[frontLeftE])) && (direction==-1))
				{
					motor[frontRight] = (gospeed-delta);
					motor[backRight]  = -gospeed;
					motor[frontLeft]  = -(gospeed-delta);
					motor[backLeft]   = gospeed;
					wait1Msec(1);
				}
				else stopmotors();
			}
			stopmotors();
		}
	}
}
//88888888888888888888888888888    spin  8888888888888888888888888888888888
void spinbot(int xx2, int rotdir)
{
	//Determine direction of rotation 1 is Right 0 is Left
	if (rotdir == 1) xx2= -xx2;
	if (rotdir == 0) xx2=  xx2;

	motor[frontRight] =  xx2;
	motor[backRight]  =  xx2;
	motor[frontLeft]  = - xx2;
	motor[backLeft]   = - xx2;

	//stop the robot
	//stopmotors();
	wait1Msec (1);
}
////88888888888888888888888888888    ROBOT TURN MOVEMENT  8888888888888888888888888888888888
////calls the turn motor routine once the desired angle is determined
//void turnrobot(int angle, int direction, int speed)
//{
//	int gyropos = 0, desiredangle = 0;
//	//get current sensor position
//	gyropos = SensorValue[gyro];

//	//writeDebugStreamLine("gyropos is: %d", gyropos);  // writes the current value of int 'x' to the debug stream
//	if (direction == 0)//this is a left turn
//		desiredangle = gyropos + angle*10;
//	else if (direction == 1)//this is a right turn
//		desiredangle = gyropos - angle*10;
//	//writeDebugStreamLine(", desiredangle is: %d", desiredangle);  // writes the current value of int 'x' to the debug stream

//	while(abs(SensorValue[gyro] - desiredangle) > 10)
//	{
//		//writeDebugStreamLine("c angle: %d", abs(SensorValue[gyro] - desiredangle));  // writes the current value of int 'x' to the debug stream

//		//call the spin right function; pass (x1, x2, y2, duration)
//		spinbot(speed,direction);

//		//writeDebugStream("gyro value: %d", SensorValue[gyro]);  // writes the current value of int 'x' to the debug stream
//	}
//	//Call stop motors function after turning
//	stopmotors();
//}
void smoverobot(int xx1, int xx2, int yy1, int duration, int automode)
{
	if (automode==0)
	{
		motor[frontRight] = yy1 - xx2 - xx1;
		motor[backRight]  =  yy1 - xx2 + xx1;
		motor[frontLeft]  = yy1 + xx2 + xx1;
		motor[backLeft]   =  yy1 + xx2 - xx1;

	}
	//This section is for automous mode movement of the base
	if (automode==1)
	{
		motor[frontRight] = (yy1 - xx2 - xx1);
		motor[backRight]  =  (yy1 - xx2 + xx1);
		motor[frontLeft]  = (yy1 + xx2 + xx1);
		motor[backLeft]   =  (yy1 + xx2 - xx1);

		wait1Msec(duration);

		//Stop the robot
		stopmotors();
	}
}
