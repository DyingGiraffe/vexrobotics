/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller
// BRight               motor         5
// FRight               motor         4
// BLeft                motor         6
// FLeft                motor         3
// RIntake              motor         14
// LIntake              motor         15
// FRoller              motor         18
// BRoller              motor         10
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
int startingLocation = 0;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (true) {
    if (Controller1.ButtonLeft.pressing() || Controller1.ButtonY.pressing()) {
      startingLocation = 0;
    } else if (Controller1.ButtonRight.pressing() || Controller1.ButtonA.pressing()) {
      startingLocation = 1;
    }
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    if (startingLocation == 1) {
      Brain.Screen.print("Starting Position RIGHT");
    } else if (startingLocation == 0) {
      Brain.Screen.print("Starting Position LEFT");
    }
  }
  Controller1.rumble(rumbleLong);
  return;
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// auton stuffing
void Forward(double distance, int vel) {
  BLeft.setPosition(0, degrees);
  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  BLeft.spin(forward);

  FLeft.spin(forward);

  BRight.spin(forward);

  FRight.spin(forward);

  waitUntil(BLeft.position(degrees) >= distance);
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    BLeft.setPosition(0, degrees);
    vex::this_thread::sleep_for(100);
  }
}

void Backwards(double distance, int vel) {
  BLeft.setPosition(0, degrees);
  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  BLeft.spin(reverse);

  FLeft.spin(reverse);

  BRight.spin(reverse);

  FRight.spin(reverse);

  waitUntil(BLeft.position(degrees) <= -distance);
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    BLeft.setPosition(0, degrees);
    vex::this_thread::sleep_for(100);
  }
}

void Left(double distance, int vel) {
  FRight.setPosition(0, degrees);
  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  BLeft.spin(reverse);

  FLeft.spin(reverse);

  BRight.spin(forward);

  FRight.spin(forward);

  waitUntil(FRight.position(degrees) >= distance);
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    FRight.setPosition(0, degrees);
    vex::this_thread::sleep_for(200);
  }
}

void Right(double distance, int vel) {
  BRight.setPosition(0, degrees);
  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  BLeft.spin(forward);

  FLeft.spin(forward);

  BRight.spin(reverse);

  FRight.spin(reverse);

  {
    waitUntil(BRight.position(degrees) <= -distance);
    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    BRight.setPosition(0, degrees);
    vex::this_thread::sleep_for(100);
  }
}

void inTake(double dgrs) {

  LIntake.setStopping(hold);

  RIntake.setStopping(hold);

  LIntake.spin(forward);

  RIntake.spin(forward);

  waitUntil(LIntake.position(degrees) == dgrs ||
            LIntake.position(degrees) > dgrs);
  {

    LIntake.stop();

    RIntake.stop();

    vex::this_thread::sleep_for(100);
  }
}

void outTake(double dgrs) {

  LIntake.setStopping(hold);

  RIntake.setStopping(hold);

  LIntake.spin(reverse);

  RIntake.spin(reverse);

  waitUntil(LIntake.position(degrees) == -dgrs ||
            LIntake.position(degrees) < -dgrs);
  {

    LIntake.stop();

    RIntake.stop();

    vex::this_thread::sleep_for(100);
  }
}

void rollOut(double dgrs) {

  FRoller.setVelocity(100, percent);

  BRoller.setVelocity(100, percent);

  FRoller.setStopping(hold);

  BRoller.setStopping(hold);

  FRoller.spin(forward);

  BRoller.spin(forward);

  waitUntil(FRoller.position(degrees) == dgrs ||
            FRoller.position(degrees) > dgrs);
  {

    FRoller.stop();

    BRoller.stop();

    vex::this_thread::sleep_for(100);
  }
}

void rollIn(double dgrs) {

  FRoller.setVelocity(100, percent);

  BRoller.setVelocity(100, percent);

  FRoller.setStopping(hold);

  BRoller.setStopping(hold);

  FRoller.spin(reverse);

  BRoller.spin(reverse);

  waitUntil(FRoller.position(degrees) == -dgrs ||
            FRoller.position(degrees) < -dgrs);
  {

    FRoller.stop();

    BRoller.stop();

    vex::this_thread::sleep_for(100);
  }
}

void ForwardIntake(double distance, int vel, int vel2) {

  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  LIntake.setVelocity(vel2, percent);

  RIntake.setVelocity(vel2, percent);

  BLeft.spin(forward);

  FLeft.spin(forward);

  BRight.spin(forward);

  FRight.spin(forward);

  LIntake.spin(forward);

  RIntake.spin(forward);

  waitUntil(BLeft.position(degrees) >= distance);
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();

    LIntake.stop();

    RIntake.stop();

    vex::this_thread::sleep_for(100);
  }
}

void ForwardIntakeRoller(double distance, int vel, int vel2, int vel3) {

  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  LIntake.setVelocity(vel2, percent);

  RIntake.setVelocity(vel2, percent);

  FRoller.setVelocity(vel3, percent);

  BRoller.setVelocity(vel3, percent);

  BLeft.spin(reverse);

  FLeft.spin(reverse);

  BRight.spin(reverse);

  FRight.spin(reverse);

  LIntake.spin(forward);

  RIntake.spin(forward);

  FRoller.spin(reverse);

  BRoller.spin(reverse);

  waitUntil(BLeft.position(degrees) <= -distance);
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();

    LIntake.stop();

    RIntake.stop();

    FRoller.stop();

    BRoller.stop();

    vex::this_thread::sleep_for(100);
  }
}
// end of auton stuffs

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  if (startingLocation == 0) {
    Left(3000, 100);
  } else {
    Right(3000, 100);
  }
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (true) {
    if (abs(Controller1.Axis3.position(percent)) > 10) {
      if (abs(Controller1.Axis1.position(percent)) > 10) { // strafing
        if (Controller1.Axis3.position(percent) > 10 &&
            Controller1.Axis1.position(percent) > 10) {
          FLeft.setVelocity(Controller1.Axis3.position(), percent);
          FRight.setVelocity(Controller1.Axis3.position() / 2, percent);
          BLeft.setVelocity(Controller1.Axis3.position(), percent);
          BRight.setVelocity(0, percent);
        }

        if (Controller1.Axis3.position(percent) > 10 &&
            Controller1.Axis1.position(percent) < 10) {
          FRight.setVelocity(Controller1.Axis3.position(), percent);
          FLeft.setVelocity(Controller1.Axis3.position() / 2, percent);
          BRight.setVelocity(Controller1.Axis3.position(), percent);
          BLeft.setVelocity(0, percent);
        }

        if (Controller1.Axis3.position(percent) < 10 &&
            Controller1.Axis1.position(percent) < 10) {
          FLeft.setVelocity(Controller1.Axis3.position(), percent);
          FRight.setVelocity(Controller1.Axis3.position() / 2, percent);
          BLeft.setVelocity(Controller1.Axis3.position(), percent);
          BRight.setVelocity(0, percent);
        }

        if (Controller1.Axis3.position(percent) < 10 &&
            Controller1.Axis1.position(percent) > 10) {
          FRight.setVelocity(Controller1.Axis3.position(), percent);
          FLeft.setVelocity(Controller1.Axis3.position() / 2, percent);
          BRight.setVelocity(Controller1.Axis3.position(), percent);
          BLeft.setVelocity(0, percent);
        }
      } // end of strafing
      else {
        FLeft.setVelocity(Controller1.Axis3.position(), percent);
        FRight.setVelocity(Controller1.Axis3.position(), percent);
        BLeft.setVelocity(Controller1.Axis3.position(), percent);
        BRight.setVelocity(Controller1.Axis3.position(), percent);
      }
    } else if (abs(Controller1.Axis1.position(percent)) > 10) {
      FLeft.setVelocity(Controller1.Axis1.position(), percent);
      FRight.setVelocity(-Controller1.Axis1.position(), percent);
      BLeft.setVelocity(Controller1.Axis1.position(), percent);
      BRight.setVelocity(-Controller1.Axis1.position(), percent);
    } else {
      FLeft.setVelocity(0, percent);
      FRight.setVelocity(0, percent);
      BLeft.setVelocity(0, percent);
      BRight.setVelocity(0, percent);
    }
    if (Controller1.ButtonL2.pressing()) {
      RIntake.setVelocity(100, percent);
      LIntake.setVelocity(100, percent);
    } else if (Controller1.ButtonL1.pressing()) {
      RIntake.setVelocity(-100, percent);
      LIntake.setVelocity(-100, percent);
    } else {
      RIntake.setVelocity(0, percent);
      LIntake.setVelocity(0, percent);
    }

    if (Controller1.ButtonR2.pressing()) {
      FRoller.setVelocity(100, percent);
      BRoller.setVelocity(100, percent);
    } else if (Controller1.ButtonR1.pressing()) {
      FRoller.setVelocity(-100, percent);
      BRoller.setVelocity(-100, percent);
    } else {
      FRoller.setVelocity(0, percent);
      BRoller.setVelocity(0, percent);
    }
    FRoller.spin(forward);
    BRoller.spin(forward);
    RIntake.spin(forward);
    LIntake.spin(forward);
    FLeft.spin(forward);
    FRight.spin(forward);
    BLeft.spin(forward);
    BRight.spin(forward);
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
