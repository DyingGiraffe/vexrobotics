/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Thu Oct 22 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FRoller              motor         9               
// BRoller              motor         10              
// IntakeRight          motor         14              
// IntakeLeft           motor         15              
// BLMotor              motor         5               
// FLMotor              motor         4               
// BRMotor              motor         6               
// FRMotor              motor         3               
// Vision               vision        19              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include "vex.h"
using namespace vex;
static void DrivePID(double distance) { // OK im going to give you step by step
                                        // tutorial on PID control LOSER-Eenreek
  double Kp =
      0.5; // Proportional of PID, if you input the exact distance you want the
           // robot to go, it most likely will overshoot, Proportional makes the
           // robot slow down when it gets closer to its target
  double Ki = 0.2; // When the robot gets too close to its target, it starts
                   // moving super slow, which is what the integral is for. It
                   // activates when error is super small

  double Kd = 0.1; // Predicts the future value of the error, and makes the
                   // speed act accordingly

  double error = 0; // How much distance is left from target

  double integral = 0; // See line 27

  double speed = 0; // Sets speed of Motors

  double derive = 0; // See line 28

  double prevError = 0; // Bet you cant guess what this does

  if (distance >= 0) {

    BLMotor.spin(forward);

    FLMotor.spin(forward);

    BRMotor.spin(forward);

    FRMotor.spin(forward);

  }

  else {

    BLMotor.spin(reverse);

    FLMotor.spin(reverse);

    BRMotor.spin(reverse);

    FRMotor.spin(
        reverse); // This part just detects which direction the robot should go
  }

  while (true) {

    error = distance -
            BLMotor.position(degrees); // Cant get data from drivetrain, so had
                                       // to use separate motor to get data

    integral = integral - error;

    if (error == 0) {

      integral = 0;
    }

    if (abs(error) > 40) {

      integral = 0;

    } // These two if-then statements keep the integral from getting to big

    derive = error - prevError;

    prevError = error;

    speed = Kp * error + Ki * integral +
            Kd * derive; // Complicated formula that sets speed

    BLMotor.setVelocity(speed, rpm);

    FLMotor.setVelocity(speed, rpm);

    BRMotor.setVelocity(speed, rpm);

    FRMotor.setVelocity(speed, rpm);

    if (speed < 25) {

      BLMotor.stop();

      FLMotor.stop();

      BRMotor.stop();

      FRMotor.stop();

      return;
    }

  } // if the speed gets to small, it stops the motors and breaks out of the
    // method
}

void Forward(double distance, int vel) {

  BLMotor.setVelocity(vel, percent);

  FLMotor.setVelocity(vel, percent);

  BRMotor.setVelocity(vel, percent);

  FRMotor.setVelocity(vel, percent);

  BLMotor.spin(forward);

  FLMotor.spin(forward);

  BRMotor.spin(forward);

  FRMotor.spin(forward);

  waitUntil(BLMotor.position(degrees) == distance ||
            BLMotor.position(degrees) > distance);
  {

    BLMotor.stop();

    FLMotor.stop();

    BRMotor.stop();

    FRMotor.stop();

    vex::this_thread::sleep_for(100);
  }
}

void Backwards(double distance, int vel) {

  BLMotor.setVelocity(vel, percent);

  FLMotor.setVelocity(vel, percent);

  BRMotor.setVelocity(vel, percent);

  FRMotor.setVelocity(vel, percent);

  BLMotor.spin(reverse);

  FLMotor.spin(reverse);

  BRMotor.spin(reverse);

  FRMotor.spin(reverse);

  waitUntil(BLMotor.position(degrees) == -distance ||
            BLMotor.position(degrees) < -distance);
  {

    BLMotor.stop();

    FLMotor.stop();

    BRMotor.stop();

    FRMotor.stop();

    vex::this_thread::sleep_for(100);
  }
}

void Left(double distance, int vel) {

  BLMotor.setVelocity(vel, percent);

  FLMotor.setVelocity(vel, percent);

  BRMotor.setVelocity(vel, percent);

  FRMotor.setVelocity(vel, percent);

  BLMotor.spin(forward);

  FLMotor.spin(forward);

  BRMotor.spin(reverse);

  FRMotor.spin(reverse);

  waitUntil(BLMotor.position(degrees) == distance ||
            BLMotor.position(degrees) > distance);
  {

    BLMotor.stop();

    FLMotor.stop();

    BRMotor.stop();

    FRMotor.stop();

    vex::this_thread::sleep_for(100);
  }
}

void Right(double distance, int vel) {

  BLMotor.setVelocity(vel, percent);

  FLMotor.setVelocity(vel, percent);

  BRMotor.setVelocity(vel, percent);

  FRMotor.setVelocity(vel, percent);

  BLMotor.spin(reverse);

  FLMotor.spin(reverse);

  BRMotor.spin(forward);

  FRMotor.spin(forward);

  waitUntil(BLMotor.position(degrees) == -distance ||
            BLMotor.position(degrees) < -distance);
  {

    BLMotor.stop();

    FLMotor.stop();

    BRMotor.stop();

    FRMotor.stop();

    vex::this_thread::sleep_for(100);
  }
}

void inTake(double dgrs) {

  IntakeLeft.setStopping(hold);

  IntakeRight.setStopping(hold);

  IntakeLeft.spin(forward);

  IntakeRight.spin(forward);

  waitUntil(IntakeLeft.position(degrees) == dgrs ||
            IntakeLeft.position(degrees) > dgrs);
  {

    IntakeLeft.stop();

    IntakeRight.stop();

    vex::this_thread::sleep_for(100);
  }
}

void outTake(double dgrs) {

  IntakeLeft.setStopping(hold);

  IntakeRight.setStopping(hold);

  IntakeLeft.spin(reverse);

  IntakeRight.spin(reverse);

  waitUntil(IntakeLeft.position(degrees) == -dgrs ||
            IntakeLeft.position(degrees) < -dgrs);
  {

    IntakeLeft.stop();

    IntakeRight.stop();

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

  waitUntil(FRoller.position(degrees) == -dgrs || FRoller.position(degrees) < -dgrs);
  {

    FRoller.stop();

    BRoller.stop();

    vex::this_thread::sleep_for(100);
  }
}

void ForwardIntake(double distance, int vel, int vel2) {

  BLMotor.setVelocity(vel, percent);

  FLMotor.setVelocity(vel, percent);

  BRMotor.setVelocity(vel, percent);

  FRMotor.setVelocity(vel, percent);

  IntakeLeft.setVelocity(vel2, percent);

  IntakeRight.setVelocity(vel2, percent);

  BLMotor.spin(forward);

  FLMotor.spin(forward);

  BRMotor.spin(forward);

  FRMotor.spin(forward);

  IntakeLeft.spin(forward);

  IntakeRight.spin(forward);

  waitUntil(BLMotor.position(degrees) == distance ||
            BLMotor.position(degrees) > distance);
  {

    BLMotor.stop();

    FLMotor.stop();

    BRMotor.stop();

    FRMotor.stop();

    IntakeLeft.stop();

    IntakeRight.stop();

    vex::this_thread::sleep_for(100);
  }
}

void ForwardIntakeRoller(double distance, int vel, int vel2, int vel3) {

  BLMotor.setVelocity(vel, percent);

  FLMotor.setVelocity(vel, percent);

  BRMotor.setVelocity(vel, percent);

  FRMotor.setVelocity(vel, percent);

  IntakeLeft.setVelocity(vel2, percent);

  IntakeRight.setVelocity(vel2, percent);

  FRoller.setVelocity(vel3, percent);

  BRoller.setVelocity(vel3, percent);

  BLMotor.spin(forward);

  FLMotor.spin(forward);

  BRMotor.spin(forward);

  FRMotor.spin(forward);

  IntakeLeft.spin(forward);

  IntakeRight.spin(forward);

  FRoller.spin(forward);

  BRoller.spin(forward);

  waitUntil(BLMotor.position(degrees) == distance ||
            BLMotor.position(degrees) > distance);
  {

    BLMotor.stop();

    FLMotor.stop();

    BRMotor.stop();

    FRMotor.stop();

    IntakeLeft.stop();

    IntakeRight.stop();

    FRoller.stop();

    BRoller.stop();

    vex::this_thread::sleep_for(100);
  }
}

void AlignWithRed(){
  int x=0; int y=0; int width=0;
  Vision.takeSnapshot(Vision__REDBOX);
  while(true){
    Vision.takeSnapshot(Vision__REDBOX);
    Brain.Screen.clearScreen();
    x=Vision.largestObject.originX;
    y=Vision.largestObject.originY;
    width=Vision.largestObject.width;
    Brain.Screen.setFillColor(red);
    Brain.Screen.drawCircle(x,y,width);
    if(Vision.largestObject.originX>10&&Vision.largestObject.originX<90){
        BLMotor.spin(forward);
        BRMotor.stop();
        
    }
    else if(Vision.largestObject.originX>110){
        BRMotor.spin(forward);
        BLMotor.stop();
    }
        else{
          BLMotor.stop();
          FLMotor.stop();
          FRMotor.stop();
          BRMotor.stop();
        }
  }
  vex::this_thread::sleep_for (100);
}

int main() {
  vexcodeInit();
  // Initializing Robot Configuration. DO NOT REMOVE!
  AlignWithRed();
/*

  rollIn(1000);

  inTake(100);

  AlignWithRed();

  ForwardIntake(500, 30, 100);
*/
  /*Forward(1000);

  Backwards(10);

  Left(100);

  Right(100);

  inTake(360);

  outTake(360);

  rollIn(360);

  rollOut(360);*/
}