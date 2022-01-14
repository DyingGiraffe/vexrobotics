using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor BRight;
extern motor BLeft;
extern motor FRight;
extern motor FLeft;
extern motor mClaw;
extern motor Intake;
extern motor RLift;
extern motor LLift;
extern motor MClaw;
extern digital_out Pneumatic;
extern inertial Inertial;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );