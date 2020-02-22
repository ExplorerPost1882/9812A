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
// Vision1              vision        5
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
  // Spin up pre-load
  SpinTreads(100);
  // wait
  wait(200, msec);
  // Drive up to cubes
  DriveAtCube(21.98, 30, Vision1__GREEN_CUBE);
  // Turn to next cube
  Turn(90, 50);
  // drive forward to next cube
  DriveAtCube(16, 30, Vision1__GREEN_CUBE);
  wait(200, msec);
  // Turn to prepare to stack cubes
  Turn(60, 50);
  // Drive up to wall to line up
  Drive(12.56, 30);
  // back up a little bit to line up to stack
  Drive(-2, 30);
  // Turn a slight bit to line up
  Turn(-25, 30);
  // drive into goal zone
  Drive(6, 75);
  // Lift tray
  TrayLift();
  // Spin flaps down to release cubes
  SpinTreads(-75);
  // Wait for 3 secs to give the cubes a chance to stack before backing out
  wait(300, msec);
  // Lower tray
  TrayLower();
  // Drive back to fully stack cubes
  Drive(-12.5, 100);
   CubeLoadStop();
  // Turn to get cube for tower
  Turn(-200, 25);
  // drive at the cube to put it in the tower and turns on the flaps
  SpinTreads(100);
  DriveAtCube(20, 25, Vision1__GREEN_CUBE);
  // Drive back slightly to get the cube in the tower and stop the treads so the
  // cube is in our arms
  CubeLoadStop();
  Drive(-6, 25);
  // lift up the arms
  ArmLiftAuto();
  // drive up to the tower
  Drive(5, 25);
  // drop the cube in the tower
  SpinTreads(-100);
  // drive away from the tower
  Drive(-8, 25);
  // lower the arms
  ArmLowerAuto();
  // All Done!!!
}

void TEST() { ArmLiftAuto(); }

void TEST2() { ArmLowerAuto(); }

void usercontrol(void) {
  // reset tray position
  // Tray.setPosition(0, degrees);

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
    // Lift arm
    Controller1.ButtonL1.pressed(ArmLift);
    // LowerArm
    Controller1.ButtonL2.pressed(ArmLower);
    // Stop moving arm up
    Controller1.ButtonL1.released(ArmStop);
    // Stop moving arm down
    Controller1.ButtonL2.released(ArmStop);
    //lift the tray
    Controller1.ButtonUp.pressed(TrayLift);
    //reset the arms completly to re-adjust
    Controller1.ButtonA.pressed(ArmReset);
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