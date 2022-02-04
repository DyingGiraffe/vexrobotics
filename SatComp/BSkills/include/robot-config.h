using namespace vex;

extern brain Brain;

// VEXcode devices
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
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );