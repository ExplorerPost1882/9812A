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
/*vex-vision-config:begin*/
signature Vision1__SIG_1 = signature (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision1__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision1__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision1__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision1__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision1__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
signature Vision1__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vision Vision1 = vision (PORT5, 50, Vision1__SIG_1, Vision1__SIG_2, Vision1__SIG_3, Vision1__SIG_4, Vision1__SIG_5, Vision1__SIG_6, Vision1__SIG_7);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}