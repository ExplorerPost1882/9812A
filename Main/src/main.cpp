/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\post1882_user                                    */
/*    Created:      Sat Nov 09 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Left                 motor         1               
// Right                motor         4               
// Tray                 motor         6               
// LeftTread            motor         7               
// RightTread           motor         8               
// LeftArm              motor         2               
// RightArm             motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "taskfile.h"
#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  vexcodeInit();
  // reset tray position
  Tray.setPosition(0, degrees);
}

void autonomous(void) {
  // Drive up to cubes
  Left.setVelocity(75, velocityUnits::pct);
  Right.setVelocity(75, velocityUnits::pct);
  Left.spinFor(1, turns, false);
  Right.spinFor(1, turns, true);
  // Spin treads to load first cube
  LeftTread.setVelocity(100, velocityUnits::pct);
  RightTread.setVelocity(100, velocityUnits::pct);
  LeftTread.spinFor(3, turns, false);
  RightTread.spinFor(3, turns, true);
  // Drive up to second cube
  Left.setVelocity(50, velocityUnits::pct);
  Right.setVelocity(50, velocityUnits::pct);
  Left.spinFor(.5, turns, false);
  Right.spinFor(.5, turns, true);
  // Spin treads to load second cube
  LeftTread.setVelocity(100, velocityUnits::pct);
  RightTread.setVelocity(100, velocityUnits::pct);
  LeftTread.spinFor(20, turns, false);
  RightTread.spinFor(20, turns, false);
  wait(200, msec);
  // Turn to prepare to stack cubes
  Left.setVelocity(50, velocityUnits::pct);
  Right.setVelocity(50, velocityUnits::pct);
  Left.spinFor(-1.458, turns, false);
  Right.spinFor(1.458, turns, true);
  // Drive up to goal zone
  Left.setVelocity(60, velocityUnits::pct);
  Right.setVelocity(60, velocityUnits::pct);
  Left.spinFor(7, turns, false);
  Right.spinFor(7, turns, false);
  wait(500, msec);
  // Lift tray
  TrayLift();
  // Spin flaps down to release cubes
  LeftTread.setVelocity(100, velocityUnits::pct);
  RightTread.setVelocity(100, velocityUnits::pct);
  LeftTread.spinFor(-20, turns, false);
  RightTread.spinFor(-20, turns, false);
  wait(5000, msec);
  // Lower tray
  TrayLower();
  // Drive back to fully stack cubes
  Left.setVelocity(60, velocityUnits::pct);
  Right.setVelocity(60, velocityUnits::pct);
  Left.spinFor(-2, turns, false);
  Right.spinFor(-2, turns, true);
}

void usercontrol(void) {
  // reset tray position
  //Tray.setPosition(0, degrees);

  while (true) {
    // Drive left
    Controller1.Axis2.changed(Drive);
    // Drive right
    Controller1.Axis1.changed(Drive);
    // Lift cubes
    Controller1.ButtonUp.pressed(TrayLift);
    // Lower cubes
    Controller1.ButtonDown.pressed(TrayLower);
    // Load cubes
    Controller1.ButtonR1.pressed(CubeLoad);
    // Stop cube load
    Controller1.ButtonR1.released(CubeLoadStop);
    // Unload/adjust cubes
    Controller1.ButtonR2.pressed(CubeLoadRev);
    // Stop cube unloading
    Controller1.ButtonR2.released(CubeLoadStop);
    //Lift arm
    Controller1.ButtonL1.pressed(ArmLift);
    //LowerArm
    Controller1.ButtonL2.pressed(ArmLower);
    //Stop moving arm up
    Controller1.ButtonL1.released(ArmStop);
    //Stop moving arm down
    Controller1.ButtonL2.released(ArmStop);
Controller1.ButtonLeft.pressed(TrayLiftSlow);
    // wait
    wait(250, msec);
  }
}

int main() {
  // Run the pre-autonomous function.
  pre_auton();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // usercontrol();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}