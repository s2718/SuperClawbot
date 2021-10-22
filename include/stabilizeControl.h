
#ifndef STABILIZE_PID_CONTROL
#define STABILIZE_PID_CONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "constants.h"

void stabilizeControl(Encoder encoderElbow, Encoder encoderShoulder, int stopTime) {
  //use convention shoulder, elbow in pairs
  double elbowPID[] = {0,0,0};

  double shoulderPID[] = {0,0,0};

  double elbowTargets[] = {(double)elbowAngle(encoderElbow),0,0};
  double shoulderTargets[] = {(double)shoulderAngle(encoderShoulder),0,0};

	for(int i = 0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
    elbowLast[i] = 0;
	}

  int elbowPower;
  int shoulderPower;

  int count = 0;

  while (stopTime < 0 || count < stopTime) {
    
    //checkSafePositions(elbowTargets, shoulderTargets);

    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    armMove(elbowPower, shoulderPower);

    count++;
    if (count%100 == 0) {
      printf("\n");
      printf("elbowP%f\n",elbowPID[0]);
      printf("elbowTarget%f\n",elbowTargets[0]);
      printf("elbowAngle%f\n",elbowAngle(encoderElbow));
      printf("\n");
      printf("shoulderP%f\n",shoulderPID[0]);
      printf("shoulderTarget%f\n",shoulderTargets[0]);
      printf("shoulderAngle%f\fn",shoulderAngle(encoderShoulder));
    }

    delay(opContInt);
  }

}

#endif
