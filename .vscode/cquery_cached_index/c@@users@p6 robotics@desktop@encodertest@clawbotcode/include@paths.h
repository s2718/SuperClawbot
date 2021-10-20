#ifndef PATHS_H_
#define PATHS_H_

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "limitSwitch.h"
#include "constants.h"
#include "kinematics.h"


#define endTime 10.0 //in seconds

int duration = (int)(endTime * 1000.0/opContInt);
double shoulderTargetsLast[numValsInt] = {0};
double elbowTargetsLast[numValsInt] = {0};

double x_func(double time) {
  return L1 + 2 * time - 10;
}

double z_func(double time) {
  return L2/2;
}


void PIDPathContol(Encoder encoderElbow, Encoder encoderShoulder) {
  //use convention shoulder, elbow in pairs
  double elbowPID[] = {0,0,0};

  double shoulderPID[] = {0,0,0};



  int elbowPower;
  int shoulderPower;

  int count = 0;
  double time = 0;
  double x;
  double z;

  double newElbowTarget;
  double newShoulderTarget;

  x = x_func(time);
  z = z_func(time);

  newElbowTarget = upperElbow(x,z);
  newShoulderTarget = upperShoulder(x,z);

  double elbowTargets[] = {(double)newElbowTarget,0,0};
  double shoulderTargets[] = {(double)newShoulderTarget,0,0};

  for (int step = 0; step < duration; step ++) {
    count ++;

    if (home_complete) {
        checkSafePositions(elbowTargets, shoulderTargets);
    }

    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

    time = step * opContInt/1000.0;

    x = x_func(time);
    z = z_func(time);

    newElbowTarget = upperElbow(x,z);
    newShoulderTarget = upperShoulder(x,z);

    calcNextTargetVals(elbowTargets, newElbowTarget, elbowTargetsLast);
    calcNextTargetVals(shoulderTargets, newShoulderTarget, shoulderTargetsLast);


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

#endif
