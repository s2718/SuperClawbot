
#ifndef TERMINATING_PID_CONTROL
#define TERMINATING_PID_CONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "limitSwitch.h"
#include "constants.h"



void PIDContol(Encoder encoderElbow, Encoder encoderShoulder, int elbowTarget, int shoulderTarget) {
  //use convention shoulder, elbow in pairs
  double elbowPID[] = {0,0,0};

  double shoulderPID[] = {0,0,0};

  double elbowTargets[] = {(double)elbowTarget,0,0};
  double shoulderTargets[] = {(double)shoulderTarget,0,0};

  int elbowPower;
  int shoulderPower;

  int count = 0;

  bool first = true;
  while(first || (abs((int)elbowPID[0]) >= 4) || (abs((int)shoulderPID[0]) >= 4)) {
    first = false;
    count ++;

    if (home_complete) {
        checkSafePositions(elbowTargets, shoulderTargets);
    }

    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    armMove(elbowPower, shoulderPower);

    if (count%100 == 0) {
      printf("\n");
      printf("elbowP%f\n",elbowPID[0]);
      printf("elbowTarget%f\n",elbowTargets[0]);
      printf("elbowAngle%f\n",elbowAngle(encoderElbow));
      printf("\n");
      printf("shoulderP%f\n",shoulderPID[0]);
      printf("shoulderTarget%f\n",shoulderTargets[0]);
      printf("shoulderAngle%f\n",shoulderAngle(encoderShoulder));
    }


    delay(opContInt);
  }

}

//
// void FindElbowLimit(Encoder encoderElbow, Encoder encoderShoulder) {
//
//   double shoulderPID[] = {0,0,0};
//
//   double shoulderTargets[] = {0,0,0};
//
//   int shoulderPower;
//
//   while(limitSwitchGetElbow() == false) {
//
//     calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);
//
//     armMove(60, pidDotProd(shoulderPID, shoulderWeights));
//
//     delay(opContInt);
//   }
//
// }

#endif
