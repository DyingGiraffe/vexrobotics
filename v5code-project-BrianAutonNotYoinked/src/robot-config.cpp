#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor FRoller = motor(PORT9, ratio18_1, false);
motor BRoller = motor(PORT10, ratio18_1, false);
motor IntakeRight = motor(PORT14, ratio18_1, false);
motor IntakeLeft = motor(PORT15, ratio18_1, true);
motor BLMotor = motor(PORT5, ratio18_1, true);
motor FLMotor = motor(PORT4, ratio18_1, true);
motor BRMotor = motor(PORT6, ratio18_1, false);
motor FRMotor = motor(PORT3, ratio18_1, false);
/*vex-vision-config:begin*/
signature Vision__REDBOX = signature (1, 6595, 8837, 7716, -1211, -391, -801, 3, 0);
signature Vision__BLUEBOX = signature (2, -3587, -1827, -2707, 6989, 10477, 8733, 3, 0);
signature Vision__GREENBOX = signature (3, -5233, -4259, -4746, -5231, -3713, -4472, 2.5, 0);
vision Vision = vision (PORT19, 55, Vision__REDBOX, Vision__BLUEBOX, Vision__GREENBOX);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}