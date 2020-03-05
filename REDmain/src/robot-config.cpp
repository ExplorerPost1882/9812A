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
motor SideWheel = motor(PORT9, ratio18_1, true);
/*vex-vision-config:begin*/
signature Vision1__ORANGE_CUBE = signature (1, 5973, 6731, 6352, -2197, -1705, -1952, 2.5, 0);
signature Vision1__PURPLE_CUBE = signature (2, 577, 1847, 1212, 4097, 7515, 5806, 2.5, 0);
signature Vision1__GREEN_CUBE = signature (3, -6607, -5151, -5878, -3583, -2449, -3016, 2.5, 0);
vision Vision1 = vision (PORT5, 50, Vision1__ORANGE_CUBE, Vision1__PURPLE_CUBE, Vision1__GREEN_CUBE);
/*vex-vision-config:end*/

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