#include "vex.h"

using namespace vex;

void Drive();

void CubeLoad ();

void CubeLoadStop();

void TrayLift (); 

void TrayLower ();

void TrayLiftSlow ();

void CubeLoadRev();

void ArmLift();

void ArmLower();

void ArmStop();

void Turn(double degrees, double speed);

void Drive(double distance, double speed);

void SpinTreads(double speed);

void DriveAtCube(double distance, double speed, vision::signature SIG);
