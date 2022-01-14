#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor BRight = motor(PORT5, ratio18_1, true);
motor BLeft = motor(PORT6, ratio18_1, false);
motor FRight = motor(PORT4, ratio18_1, true);
motor FLeft = motor(PORT3, ratio18_1, false);
motor mClaw = motor(PORT14, ratio18_1, false);
motor Intake = motor(PORT15, ratio18_1, false);
motor RLift = motor(PORT9, ratio18_1, false);
motor LLift = motor(PORT10, ratio18_1, true);
motor MClaw = motor(PORT16, ratio18_1, false);
digital_out Pneumatic = digital_out(Brain.ThreeWirePort.H);
inertial Inertial = inertial(PORT11);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}