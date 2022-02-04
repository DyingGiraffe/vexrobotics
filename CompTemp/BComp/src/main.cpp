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
// BLeft                motor         6               
// FRight               motor         4               
// FLeft                motor         3               
// mClaw                motor         14              
// Intake               motor         15              
// RLift                motor         9               
// LLift                motor         10              
// MClaw                motor         16              
// Pneumatic            digital_out   H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

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
  Pneumatic=false;
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
void Forward(double distance, int vel) {
  BLeft.setPosition(0,degrees);
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
    BLeft.setPosition(0,degrees);
    vex::this_thread::sleep_for(100);
  }
}
void Backwards(double distance, int vel) {
  BLeft.setPosition(0,degrees);
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
    BLeft.setPosition(0,degrees);
    vex::this_thread::sleep_for(100);
  }
}
void Left(double distance, int vel) {
  FRight.setPosition(0,degrees);
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
    FRight.setPosition(0,degrees);
    vex::this_thread::sleep_for(200);
  }
}
void Right(double distance, int vel) {
  BRight.setPosition(0,degrees);
  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  BLeft.spin(forward);

  FLeft.spin(forward);

  BRight.spin(reverse);

  FRight.spin(reverse);

  {
  waitUntil(BRight.position(degrees)<=-distance);
    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    BRight.setPosition(0,degrees);
    vex::this_thread::sleep_for(100);
  }
}
void raiseLift (double distance, int vel2)
{
  LLift.setPosition(0,degrees);
  RLift.setPosition(0,degrees);
  LLift.setVelocity(vel2,percent);
  RLift.setVelocity(vel2,percent);
  LLift.spin(forward);
  RLift.spin(forward);
  waitUntil(RLift.position(degrees) >= distance);
    {
      LLift.stop();
      RLift.stop();
    }
} 
void lowerLift (double distance, int vel)
{
  LLift.setPosition(0,degrees);
  RLift.setPosition(0,degrees);
  LLift.setVelocity(vel,percent);
  RLift.setVelocity(vel,percent);
  RLift.spin(reverse);
  LLift.spin(reverse);
  waitUntil(LLift.position(degrees) >= distance);
    {
      LLift.stop();
      RLift.stop();
    }
}

void intake(double distance, int vel) {
  Intake.setPosition(0, degrees);
  Intake.setVelocity(vel, percent);
  Intake.spin(reverse);
  waitUntil(Intake.position(degrees) <= -distance);
  {
    Intake.stop();
  }
}

void outtake(double distance, int vel) {
  Intake.setPosition(0, degrees);
  Intake.setVelocity(vel, percent);
  Intake.spin(forward);
  waitUntil(Intake.position(degrees) >= distance);
  {
    Intake.stop();
  }
}


void openClaws(int distance, int vel) {
  mClaw.setPosition(0, degrees);
  mClaw.setVelocity(vel, percent);
  mClaw.spin(forward);
  waitUntil(mClaw.position(degrees) >= distance);
  {
    mClaw.stop();
  }
}

void closeClaw(int distance, int vel) {
  mClaw.setPosition(0, degrees);
  mClaw.setVelocity(vel, percent);
  mClaw.spin(reverse);
  waitUntil(mClaw.position(degrees) <= -distance);
  {
    mClaw.stop();
  }
}

void pneumaticsOn() {
  Pneumatic=1;
}

void pneumaticsOff(){
  Pneumatic=0;
}
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.

Pneumatic=false;
  Forward(1200, 100);
  vex::this_thread::sleep_for(100);
  Pneumatic=true;
  vex::this_thread::sleep_for(500);
  Backwards(600, 100);
  vex::this_thread::sleep_for(200);
  Left(300, 70);
  vex::this_thread::sleep_for(100);
  Backwards(320, 100);
  closeClaw(1100,100);
  outtake(600,40);
  vex::this_thread::sleep_for(100);
  Forward(250,80);
  
  
  // ..........................................................................
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
  int pneumaticIO = 0;
  while (1) {
    if (abs(Controller1.Axis3.position(percent)) > 10) {
      if (abs(Controller1.Axis1.position(percent)) > 10) { // strafing
        if (Controller1.Axis3.position(percent) > 10 &&
            Controller1.Axis1.position(percent) > 10) {
          FLeft.setVelocity(Controller1.Axis3.position(), percent);
          FRight.setVelocity(Controller1.Axis3.position() / 2, percent);
          BLeft.setVelocity(Controller1.Axis3.position(), percent);
          BRight.setVelocity(Controller1.Axis3.position() / 2, percent);
        }

        if (Controller1.Axis3.position(percent) > 10 &&
            Controller1.Axis1.position(percent) < -10) {
          FRight.setVelocity(Controller1.Axis3.position(), percent);
          FLeft.setVelocity(Controller1.Axis3.position() / 2, percent);
          BRight.setVelocity(Controller1.Axis3.position(), percent);
          BLeft.setVelocity(Controller1.Axis3.position() / 2, percent);
        }

        if (Controller1.Axis3.position(percent) < -10 &&
            Controller1.Axis1.position(percent) < -10) {
          FLeft.setVelocity(Controller1.Axis3.position(), percent);
          FRight.setVelocity(Controller1.Axis3.position() / 2, percent);
          BLeft.setVelocity(Controller1.Axis3.position(), percent);
          BRight.setVelocity(Controller1.Axis3.position() / 2, percent);
        }

        if (Controller1.Axis3.position(percent) < -10 &&
            Controller1.Axis1.position(percent) > 10) {
          FRight.setVelocity(Controller1.Axis3.position(), percent);
          FLeft.setVelocity(Controller1.Axis3.position() / 2, percent);
          BRight.setVelocity(Controller1.Axis3.position(), percent);
          BLeft.setVelocity(Controller1.Axis3.position() / 2, percent);
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

    // liftHold = RLift.position(degrees) / 10;
    // if (liftHold >= 30)
    //   liftHold = 30;
    if (Controller1.ButtonR1.pressing()) {
      //
      if (Controller1.ButtonL2.pressing()) {
        Intake.setVelocity(60, percent);
        RLift.setVelocity(60, percent);
        LLift.setVelocity(60, percent);
      } else if (Controller1.ButtonL1.pressing()) {
        Intake.setVelocity(-60, percent);
        RLift.setVelocity(60, percent);
        LLift.setVelocity(60, percent);
      } else {
        RLift.setVelocity(60, percent);
        LLift.setVelocity(60, percent);
        Intake.setVelocity(0, percent);
      }
      //
    } else if (Controller1.ButtonR2.pressing()) {
      //
      if (Controller1.ButtonL2.pressing()) {
        Intake.setVelocity(60, percent);
        RLift.setVelocity(-40, percent);
        LLift.setVelocity(-40, percent);
      } else if (Controller1.ButtonL1.pressing()) {
        Intake.setVelocity(-60, percent);
        RLift.setVelocity(-40, percent);
        LLift.setVelocity(-40, percent);
      } else {
        RLift.setVelocity(-40, percent);
        LLift.setVelocity(-40, percent);
        Intake.setVelocity(0, percent);
      }
      //
    } else {
      RLift.setVelocity(0, percent);
      LLift.setVelocity(0, percent);
      RLift.stop(hold);
      LLift.stop(hold);
    }
    if (Controller1.ButtonUp.pressing()) {
      mClaw.setVelocity(100, percent);
    } else if (Controller1.ButtonDown.pressing()) {
      mClaw.setVelocity(-100, percent);
    } else {
      mClaw.setVelocity(0, percent);
      mClaw.setStopping(hold);
    }

    // if (MClaw.position(degrees) > 30) {
    //  MClaw.setVelocity(-10, percent);
    // } else
    if (Controller1.ButtonX.pressing()) {
      MClaw.setVelocity(50, percent);
    } else if (Controller1.ButtonB.pressing()) {
      MClaw.setVelocity(-50, percent);
    } else {
      MClaw.setVelocity(0, percent);
      MClaw.setStopping(hold);
    }

    if (Controller1.ButtonL2.pressing()) {
      //
      if (Controller1.ButtonR1.pressing()) {
        RLift.setVelocity(60, percent);
        LLift.setVelocity(60, percent);
        Intake.setVelocity(60, percent);
      } else if (Controller1.ButtonR2.pressing()) {
        RLift.setVelocity(-40, percent);
        LLift.setVelocity(-40, percent);
        Intake.setVelocity(60, percent);
      } else {
        Intake.setVelocity(60, percent);
        RLift.setVelocity(0, percent);
        LLift.setVelocity(0, percent);
      }
      //
    } else if (Controller1.ButtonL1.pressing()) {
      //
      if (Controller1.ButtonR1.pressing()) {
        RLift.setVelocity(60, percent);
        LLift.setVelocity(60, percent);
        Intake.setVelocity(-60, percent);
      } else if (Controller1.ButtonR2.pressing()) {
        RLift.setVelocity(-40, percent);
        LLift.setVelocity(-40, percent);
        Intake.setVelocity(-60, percent);
      } else {
        Intake.setVelocity(-60, percent);
        RLift.setVelocity(0, percent);
        LLift.setVelocity(0, percent);
      }
      //
    } else {
      Intake.setVelocity(0, percent);
    }
    pneumaticIO = Pneumatic;
    if (Controller1.ButtonX.pressing()) {
      if (pneumaticIO == 1) {
        Pneumatic = 0;
        vex::this_thread::sleep_for(200);
      } else {
        Pneumatic = 1;
        vex::this_thread::sleep_for(200);
      }
    }

    RLift.spin(forward);
    LLift.spin(forward);
    mClaw.spin(forward);
    Intake.spin(forward);
    FLeft.spin(forward);
    FRight.spin(forward);
    BLeft.spin(forward);
    BRight.spin(forward);
    MClaw.spin(forward);
  }
  wait(20, msec); // Sleep the task for a short amount of time to
                  // prevent wasted resources.
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
  if (Controller1.ButtonLeft.pressing())
    {
        Brain.Screen.print('left');
        


    }
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
