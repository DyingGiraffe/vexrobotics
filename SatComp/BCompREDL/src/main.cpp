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
// Inertial             inertial      11              
// Bonnet               digital_out   G               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
int timing = 0;
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
  Intake.setStopping(hold);
  Intake.stop();
  Pneumatic=false;
  Bonnet=false;
  Inertial.calibrate();
  while (Inertial.isCalibrating()) {
    vex::this_thread::sleep_for(10);
  }
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
  BLeft.setPosition(0, degrees);
  BLeft.setVelocity(vel, percent);

  FLeft.setVelocity(vel, percent);

  BRight.setVelocity(vel, percent);

  FRight.setVelocity(vel, percent);

  BLeft.spin(forward);

  FLeft.spin(forward);

  BRight.spin(forward);

  FRight.spin(forward);

  waitUntil(FRight.position(degrees) >= distance);
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    BLeft.setPosition(0, degrees);
    // vex::this_thread::sleep_for(100);
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
    // vex::this_thread::sleep_for(100);
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

  waitUntil((Inertial.rotation(degrees) <= -distance));
  {

    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    FRight.setPosition(0, degrees);
    // vex::this_thread::sleep_for(200);
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
    waitUntil((Inertial.rotation(degrees) <= -distance));
    BLeft.stop();

    FLeft.stop();

    BRight.stop();

    FRight.stop();
    BRight.setPosition(0, degrees);
    // vex::this_thread::sleep_for(100);
  }
}
void raiseLift(double distance, int vel2) {
  RLift.setPosition(0, degrees);
  LLift.setPosition(0, degrees);
  RLift.setVelocity(vel2, percent);
  LLift.setVelocity(vel2, percent);
  RLift.spin(forward);
  LLift.spin(forward);
  waitUntil(RLift.position(degrees) >= distance);
  RLift.setStopping(hold);
  LLift.setStopping(hold);
  RLift.stop();
  LLift.stop();
}
void intake(double distance, int vel) {
  Intake.setPosition(0, degrees);
  Intake.setVelocity(vel, percent);
  Intake.spin(reverse);
  waitUntil(Intake.position(degrees) <= -distance);
  { Intake.stop(); }
}

void outtake(double distance, int vel) {
  Intake.setPosition(0, degrees);
  Intake.setVelocity(vel, percent);
  Intake.spin(forward);
  waitUntil(Intake.position(degrees) >= distance);
  { Intake.stop(); }
}

void openClaws(int distance, int vel) {
  mClaw.setPosition(0, degrees);
  mClaw.setVelocity(vel, percent);
  mClaw.spin(forward);
  waitUntil(mClaw.position(degrees) >= distance);
  {
    mClaw.setStopping(hold);
    mClaw.stop();
  }
}

void closeClaw(int distance, int vel) {
  mClaw.setPosition(0, degrees);
  mClaw.setVelocity(vel, percent);
  mClaw.spin(reverse);
  waitUntil(mClaw.position(degrees) <= -distance);
  {
    mClaw.setStopping(hold);
    mClaw.stop();
  }
}

void closeClawTimed(double milliseconds, int vel) {
  timing=0;
  mClaw.setPosition(0, degrees);
  mClaw.setVelocity(vel, percent);
  mClaw.spin(reverse);
  while (timing <= milliseconds) {
    vex::this_thread::sleep_for(10);
    timing += 10;
  }
  mClaw.setStopping(hold);
  mClaw.stop();
}

/*void AlignWithRed() {
  int x = 0;
  int y = 0;
  int width = 0;
  Vision.takeSnapshot(Vision__REDBOX);
  while (true) {
    Vision.takeSnapshot(Vision__REDBOX);
    Brain.Screen.clearScreen();
    x = Vision.largestObject.originX;
    y = Vision.largestObject.originY;
    width = Vision.largestObject.width;
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawCircle(x, y, width);
    if (Vision.largestObject.originX > 10 &&
        Vision.largestObject.originX < 60) {
      BRight.setVelocity(20, percent);
      FRight.setVelocity(20, percent);
      FLeft.setVelocity(20, percent);
      BLeft.setVelocity(20, percent);

      BLeft.spin(forward);
      FLeft.spin(forward);
      FRight.spin(reverse);
      BRight.spin(reverse);

    } else if (Vision.largestObject.originX > 170) {
      BRight.setVelocity(20, percent);
      FRight.setVelocity(20, percent);
      FLeft.setVelocity(20, percent);
      BLeft.setVelocity(20, percent);
      BRight.spin(forward);
      FRight.spin(forward);
      FLeft.spin(reverse);
      BLeft.spin(reverse);
    }
  }

  vex::this_thread::sleep_for(100);
}*/
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  while (Inertial.isCalibrating()) {
    vex::this_thread::sleep_for(10);
  }
  Pneumatic = false;
  Forward(1300, 100);
  vex::this_thread::sleep_for(100);
  Pneumatic = true;
  vex::this_thread::sleep_for(500);
  Backwards(1250, 100);
  raiseLift(100, 50);
  vex::this_thread::sleep_for(200);
  Left(55, 70);
  vex::this_thread::sleep_for(100);
  openClaws(1500, 100);
  Backwards(160, 100);
  closeClawTimed(2000, 100);
  Bonnet=true;
  outtake(700, 40);
  vex::this_thread::sleep_for(100);
  Forward(150, 80);

  // Forward
  // pneumaticsOn
  // Backwards
  // Left
  // mClaw

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
  int pneumaticIO2 = 0;
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
        RLift.setVelocity(50, percent);
        LLift.setVelocity(50, percent);
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

      pneumaticIO2=Bonnet;
      if(Controller1.ButtonB.pressing()){
          if(pneumaticIO2==1){
            Bonnet=0;
            vex::this_thread::sleep_for(200);
          }
          else{ 
          Bonnet=1;
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
    Brain.Screen.print(FRight.temperature(percent));
    Brain.Screen.clearScreen();
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
  if (Controller1.ButtonLeft.pressing()) {
    Brain.Screen.print('left');
  }
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
