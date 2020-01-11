#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor Right = motor(PORT4, ratio18_1, true);
motor Left = motor(PORT1, ratio18_1, false);
motor Tray = motor(PORT6, ratio36_1, true);
motor LeftTread = motor(PORT8, ratio18_1, false);
motor RightTread = motor(PORT7, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}