#include "vex.h"

using namespace vex;

void Drive();

void CubeLoad ();

void CubeLoadStop();

void TrayLift (); 

void TrayLower ();

void CubeLoadRev();

void DriveAtCube(double distance, double speed, vision::signature SIG);

void ArmLift();

void ArmLower();

void ArmStop();

void ArmReset();

void Turn(double degrees, double speed);

void Drive(double distance, double speed);

void SpinTreads(double speed);

void SideDriveLeft();
void SideDriveRight();
void SideStop();
void SideDriveAuto(double distance, double speed);
void LeftWheelAdjust();