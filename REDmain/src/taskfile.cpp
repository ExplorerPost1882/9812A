#include "vex.h"

using namespace vex;

// Diameter of base (diagonal from wheel to wheel)-INCHES
const double DB = 17;
// Diameter of wheels-INCHES
const double DW = 4.125;

// finds circumfrence of turn
const double CB = (DB * M_PI);
// finds circumfrence of wheels, also being how far it travels in one rotation
const double CW = (DW * M_PI);

// variable to make one full rotation
const double RotationsToTurn360 = (CB / CW);

void Drive() {

  int deadband = 5;

  while (true) {
    // Get the velocity percentage of the left motor. (Axis3)
    int leftMotorSpeed = Controller1.Axis3.position();
    // Get the velocity percentage of the right motor. (Axis2)
    int rightMotorSpeed = Controller1.Axis2.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(leftMotorSpeed) < deadband) {
      // Set the speed to zero.
      Left.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      Left.setVelocity(leftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(rightMotorSpeed) < deadband) {
      // Set the speed to zero
      Right.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      Right.setVelocity(rightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    Left.spin(forward);
    Right.spin(forward);

    wait(25, msec);
  }
}

// Spin the treads to take in cubes. Use a negative speed to release a stack
void SpinTreads(double speed) {
  LeftTread.spin(forward, speed, velocityUnits::pct);
  RightTread.spin(forward, speed, velocityUnits::pct);
}

// Spins flipping arms to load cube into tray
void CubeLoad() { 
  SpinTreads(100); 
}

// spins flippers down to unload cubes
void CubeLoadRev() {
  SpinTreads(-75);
}

// stops spinning the flippers
void CubeLoadStop() {
  LeftTread.setVelocity(0, velocityUnits::pct);
  RightTread.setVelocity(0, velocityUnits::pct);
}

bool armsStopped = true;

// lift arms to lift cubes
void ArmLift() {
  LeftArm.setPosition(0, turns);
  RightArm.setPosition(0, turns);
  // Set speed of arms
  LeftArm.setVelocity(50, velocityUnits::pct);
  RightArm.setVelocity(50, velocityUnits::pct);
  // spin arms to lift
  LeftArm.spin(forward);
  RightArm.spin(forward);
  armsStopped = false;

  while (!armsStopped) {
    LeftArm.setVelocity(50.0 + RightArm.position(degrees) -
                            LeftArm.position(degrees),
                        velocityUnits::pct);
    RightArm.setVelocity(50.0 + LeftArm.position(degrees) -
                             RightArm.position(degrees),
                         velocityUnits::pct);
  }
}
// lower arms to lower cubes
void ArmLower() {
  // Set speed of arms
  LeftArm.setVelocity(25, velocityUnits::pct);
  RightArm.setVelocity(25, velocityUnits::pct);
  // spin arms to lower
  LeftArm.spin(reverse);
  RightArm.spin(reverse);
}
// stop arms
void ArmStop() {
  LeftArm.setStopping(hold);
  RightArm.setStopping(hold);
  LeftArm.stop();
  RightArm.stop();
  armsStopped = true;
}
// lift the tray to drop the cubes
void TrayLift() {
  if (Tray.position(degrees) == 900) {
    wait(100, msec);
  } else {
    Tray.setVelocity(100, velocityUnits::pct);
    Tray.spinToPosition(-850, rotationUnits::deg);
  }
}

// lift the tray slowly to drop the cubes
void TrayLiftSlow() {
  if (Tray.position(degrees) == 900) {
    wait(100, msec);
  } else {
    Tray.setVelocity(50, velocityUnits::pct);
    Tray.spinToPosition(-850, rotationUnits::deg);
  }
}

// lower the tray back to the cube loading position
void TrayLower() {
  if (Tray.position(degrees) == 0) {
    wait(100, msec);
  } else {
    Tray.setVelocity(100, velocityUnits::pct);
    Tray.spinToPosition(-30, rotationUnits::deg);
  }
}

// Turn the robot a number of degrees. Positive is Right, Negative is Left,
// Speed is in Percent
void Turn(double degrees, double speed) {
  double fractionOfTurns = degrees / 360.0;
  double rotationsToTurnDegreesGiven = fractionOfTurns * RotationsToTurn360;
  Left.spinFor(forward, rotationsToTurnDegreesGiven, rotationUnits::rev, speed,
               velocityUnits::pct, false);
  Right.spinFor(reverse, rotationsToTurnDegreesGiven, rotationUnits::rev, speed,
                velocityUnits::pct, true);
}

// Drive the robot a number of inches. Distance is in inches, speed is in
// percent. Drive back using a negative velocity
void Drive(double distance, double speed) {
  double rotations = distance / CW;
  Left.spinFor(forward, rotations, rotationUnits::rev, speed,
               velocityUnits::pct, false);
  Right.spinFor(forward, rotations, rotationUnits::rev, speed,
                velocityUnits::pct, true);
}
