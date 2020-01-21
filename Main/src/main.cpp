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
  //Spin up pre-load
  SpinTreads(100);
  //wait
  wait(200, msec);
  // Drive up to cubes
  Drive(21.98, 30);
  //Turn to next cube
  Turn(90, 50);
  //drive forward to next cube
  Drive(9.42, 30);
  wait(200, msec);
 // Turn to prepare to stack cubes
  Turn(45, 50);
  // Drive up to goal zone
  Drive(12.56, 60);
  // Lift tray
  TrayLift();
  // Spin flaps down to release cubes
  SpinTreads(-75);
  // Wait for 3 secs to give the cubes a chance to stack before backing out
  wait(300, msec);
  // Lower tray
  TrayLower();
  // Drive back to fully stack cubes
  Drive(25.12, -60);
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