using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor BRight;
extern motor FRight;
extern motor BLeft;
extern motor FLeft;
extern motor RIntake;
extern motor LIntake;
extern motor FRoller;
extern motor BRoller;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );