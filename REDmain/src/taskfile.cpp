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

// Dirve to a specific cube
void DriveAtCube(double distance, double speed, vision::signature SIG) {
  double rotations = distance / CW;

  const int middle = 316 / 2 - 58;
  const int dead = 5;

  int leftSpeed = speed;
  int rightSpeed = speed;

  Right.resetRotation();

  Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
  Right.spin(directionType::fwd, rightSpeed, velocityUnits::pct);

  bool keepLooking = true;
  while (Right.rotation(rotationUnits::rev) < rotations) {
    Vision1.takeSnapshot(SIG);
    if(keepLooking && Vision1.largestObject.exists && Vision1.largestObject.width > 5 &&
        Vision1.largestObject.height < 120) {
      Brain.Screen.setPenColor(vex::color::white);
      Brain.Screen.setFillColor(vex::color::orange);
      Brain.Screen.drawRectangle(0, 0, 480, 240);

      int x = Vision1.largestObject.centerX;
      int diff = middle - x;
      if (abs(diff) > dead) {
        leftSpeed = leftSpeed - diff / 40;
      } else {
        leftSpeed = speed;
      }
      Left.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
    } else {
      if(keepLooking && Vision1.largestObject.exists){
        keepLooking =  Vision1.largestObject.height < 120;
      }
      Left.spin(directionType::fwd, speed, velocityUnits::pct);
      Right.spin(directionType::fwd, speed, velocityUnits::pct);
      Brain.Screen.clearScreen();
    }
    task::sleep(50);
  }
  Left.stop();
  Right.stop();
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

//reset the arms
void ArmReset(){
  LeftArm.setStopping(coast);
  RightArm.setStopping(coast);
  LeftArm.stop();
  RightArm.stop();
}
// lift the tray to drop the cubes
void TrayLift() {
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
  Left.spinFor(forward, rotationsToTurnDegreesGiven, rotationUnits::rev, speed, velocityUnits::pct, false);
  Right.spinFor(reverse, rotationsToTurnDegreesGiven, rotationUnits::rev, speed, velocityUnits::pct, true);
}

// Drive the robot a number of inches. Distance is in inches, speed is in
// percent. Drive back using a negative velocity
void Drive(double distance, double speed) {
  double rotations = distance / CW;
  Left.spinFor(forward, rotations, rotationUnits::rev, speed, velocityUnits::pct, false);
  Right.spinFor(forward, rotations, rotationUnits::rev, speed, velocityUnits::pct, true);
}

//drive sideways in autonomous
void SideDriveAuto(double distance, double speed) {
  double rotations = distance / CW;
  Left.setStopping(hold);
  Right.setStopping(hold);
  Right.stop();
  Left.stop();
  SideWheel.spinFor(rotations, rotationUnits::rev, speed, velocityUnits::pct);
}

// drive sideways
void SideDriveLeft() {
  Left.setStopping(hold);
  Right.setStopping(hold);
  Right.stop();
  Left.stop();
  SideWheel.spin(directionType::fwd, 100, velocityUnits::pct);
}

void SideDriveRight() {
  Left.setStopping(hold);
  Right.setStopping(hold);
  Right.stop();
  Left.stop();
  SideWheel.spin(directionType::rev, 100, velocityUnits::pct);
}

void SideStop() {
  Left.setStopping(coast);
  Right.setStopping(coast);
  Right.stop();
  Left.stop();
  SideWheel.stop();
}

// Adjust the wheel to get out of the zone in auto
void LeftWheelAdjust() {
  Left.spinFor(directionType::rev, .5, rotationUnits::rev, 100,
                velocityUnits::pct);
}