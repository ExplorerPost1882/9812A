#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Left = motor(PORT1, ratio18_1, false);
motor Right = motor(PORT4, ratio18_1, true);
motor Tray = motor(PORT6, ratio36_1, true);
motor LeftTread = motor(PORT7, ratio36_1, false);
motor RightTread = motor(PORT8, ratio36_1, true);
motor LeftArm = motor(PORT2, ratio36_1, false);
motor RightArm = motor(PORT3, ratio36_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}