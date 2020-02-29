using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor Left;
extern motor Right;
extern motor Tray;
extern motor LeftTread;
extern motor RightTread;
extern motor LeftArm;
extern motor RightArm;
extern motor SideWheel;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );