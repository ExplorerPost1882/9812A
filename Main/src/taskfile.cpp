#include "vex.h"

using namespace vex;

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

// Spins flipping arms to load cube into tray
void CubeLoad() {
  LeftTread.setVelocity(75, velocityUnits::pct);
  RightTread.setVelocity(75, velocityUnits::pct);

  LeftTread.spin(forward);
  RightTread.spin(forward);
}

// spins flippers down to unload cubes
void CubeLoadRev() {
  LeftTread.setVelocity(75, velocityUnits::pct);
  RightTread.setVelocity(75, velocityUnits::pct);

  LeftTread.spin(reverse);
  RightTread.spin(reverse);
}

// stops spinning the flippers
void CubeLoadStop() {
  LeftTread.setVelocity(0, velocityUnits::pct);
  RightTread.setVelocity(0, velocityUnits::pct);
}
// lift arms to lift cubes
void ArmLift() {
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
  LeftArm.setVelocity(50, velocityUnits::pct);
  RightArm.setVelocity(50, velocityUnits::pct);
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
}
// lift the tray to drop the cubes
void TrayLift() {
  if (Tray.position(degrees) == 900) {
    wait(100, msec);
  } else {
    Tray.setVelocity(100, velocityUnits::pct);
    Tray.spinToPosition(-890, rotationUnits::deg);
  }
}

// lower the tray back to the cube loading position
void TrayLower() {
  if (Tray.position(degrees) == 0) {
    wait(100, msec);
  } else {
    Tray.setVelocity(100, velocityUnits::pct);
    Tray.spinToPosition(0, rotationUnits::deg);
  }
}
