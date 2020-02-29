#include "vex.h"

using namespace vex;

void Drive();

void CubeLoad ();

void CubeLoadStop();

void TrayLower ();

void TrayLift ();

void TrayAdjust();

void CubeLoadRev();

void ArmLift();

void ArmLiftAuto();

void ArmLower();

void ArmLowerAuto();

void ArmStop();

void ArmReset();

void Turn(double degrees, double speed);

void Drive(double distance, double speed);

void SpinTreads(double speed);

void DriveAtCube(double distance, double speed, vision::signature SIG);

void SlideOnCube(double max, double speed, vision::signature SIG);

void SideDriveLeft();
void SideDriveRight();
void SideStop();
void SideDriveAuto(double distance, double speed);
void RightWheelAdjust();