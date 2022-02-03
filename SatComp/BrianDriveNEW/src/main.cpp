/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Tue Dec 22 2020                                           */
/*    Description:  V5 project                                                */
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
// MogoHooks            motor         14              
// Intake               motor         15              
// RLift                motor         9               
// LLift                motor         10              
// MClaw                motor         16              
// pClaw                digital_out   H               
// Bonnet               digital_out   G               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  int pneumaticIO = 0;
  int pneumaticIO2 = 0;
  MClaw.setPosition(0, degrees);
  // RLift.setPosition(0, degrees);
  // LLift.setPosition(0, degrees);
  // int liftHold = RLift.position(degrees) / 5;
  while (true) {
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
      MogoHooks.setVelocity(100, percent);
    } else if (Controller1.ButtonDown.pressing()) {
      MogoHooks.setVelocity(-100, percent);
    } else {
      MogoHooks.setVelocity(0, percent);
      MogoHooks.setStopping(hold);
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
      pneumaticIO=pClaw;
      if(Controller1.ButtonX.pressing()){
          if(pneumaticIO==1){
            pClaw=0;
            vex::this_thread::sleep_for(200);
          }
          else{ 
          pClaw=1;
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
    MogoHooks.spin(forward);
    Intake.spin(forward);
    FLeft.spin(forward);
    FRight.spin(forward);
    BLeft.spin(forward);
    BRight.spin(forward);
    MClaw.spin(forward);
  }
}