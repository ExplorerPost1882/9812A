using namespace vex;

extern brain Brain;

using signature = vision::signature;

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
extern signature Vision1__ORANGE_CUBE;
extern signature Vision1__PURPLE_CUBE;
extern signature Vision1__GREEN_CUBE;
extern signature Vision1__SIG_4;
extern signature Vision1__SIG_5;
extern signature Vision1__SIG_6;
extern signature Vision1__SIG_7;
extern vision Vision1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );