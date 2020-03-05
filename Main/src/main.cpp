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
// SideWheel            motor         9               
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
  Drive(21.98, 30);
  //Back up slightly
  Drive(-2.5, 25);
  // Turn to next cube
  Turn(89, 50);
  // drive forward to next cube
  DriveAtCube(16, 30, Vision1__GREEN_CUBE);
  wait(700, msec);
  //drive back slightly
  Drive(-3, 25);
  //Drive to the wall to line up near the zone
  SideDriveAuto(-30,100);
  Turn(5, 80);
  //drive slightly away from thew wall
  SideDriveAuto(4, 25);
  //turn off the treads
  CubeLoadStop();
  // drive into goal zone and wait a sec
  Drive(12, 50);
  wait(500, msec);
  // Spin flaps down to release cubes
  SpinTreads(-50);
  // Lift tray
  TrayLift();
  // Wait for 3 secs to give the cubes a chance to stack before backing out
  wait(300, msec);
  // Lower tray
  TrayLower();
  // Drive back to fully stack cubes
  RightWheelAdjust();
  Drive(-12.5, 90);
  CubeLoadStop();
  wait(600, msec);
  //line up against the wall
  SideDriveAuto(-15, 100);
  Turn(-10, 100);
  SideDriveAuto(-5, 100);
  //drive away from the wall
  SideDriveAuto(10, 100);
  //turn 90 degrees
  Turn(-90, 50);
  //back up on wall
  Drive(-12, 50);
  //drive to the cube
  Drive(36.5, 40);
  //line up sideways
  SlideOnCube(15, 100, Vision1__GREEN_CUBE);
  //pick up cube
  SpinTreads(75);
  wait(200, msec);
  Drive(13, 10);
  wait(600, msec);
  CubeLoadStop();
  Drive(-3,25);
  //lift arms
  ArmLiftAuto();
  //eject cube
  SpinTreads(-100);
  wait(2000, msec);
  //lower arms
  ArmReset();
  CubeLoadStop();

  /*
  //back up to wall
  Drive(-50, 70);
  //go a small distance away from the wall and turn
  Drive(9, 70);
  Turn(-90, 70);
  //line up against the wall and drive slightly away
  SideDriveAuto(7, 80);
  SideDriveAuto(10, 80);
  //drive up to the cube
  Drive(18, 80);
  //line up on the cube
  SlideOnCube(10, 80, Vision1__GREEN_CUBE);
  //pick up cube
  SpinTreads(75);
  wait(200, msec);
  Drive(13, 10);
  wait(600, msec);
  CubeLoadStop();
  Drive(-3,25);
  //lift arms
  ArmLiftAuto();
  //eject cube
  SpinTreads(-100);
  wait(2000, msec);
  //lower arms
  ArmReset();
  CubeLoadStop();
  */
}

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
    //Adjust the tray
    Controller1.ButtonY.pressed(TrayAdjust);
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

    Controller1.ButtonRight.pressed(SideDriveRight);
    Controller1.ButtonLeft.pressed(SideDriveLeft);
    Controller1.ButtonLeft.released(SideStop);
    Controller1.ButtonRight.released(SideStop);



    // wait
    wait(250, msec);
  }
}

int main() {
  // Run the pre-autonomous function.
  pre_auton();
  autonomous();
  //Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // usercontrol();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}