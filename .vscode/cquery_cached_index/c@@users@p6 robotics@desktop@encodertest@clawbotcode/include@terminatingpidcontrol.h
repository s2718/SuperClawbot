
#ifndef TERMINATING_PID_CONTROL
#define TERMINATING_PID_CONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "limitSwitch.h"

int dist(a,b) {
  if (a > b) {
    return a - b;
  }
  else {
    return b - a;
  }
}


void PIDContol(Encoder encoderElbow, Encoder encoderShoulder, int elbowTarget, int shoulderTarget) {
  //use convention shoulder, elbow in pairs
  double elbowPID[] = {0,0,0};
  double elbowWeights[] = {15,0,0};

  double shoulderPID[] = {0,0,0};
  double shoulderWeights[] = {5,0,0};

  double elbowTargets[] = {(double)elbowTarget,0,0};
  double shoulderTargets[] = {(double)shoulderTarget,0,0};

  int numValsInt = 50;

  int shoulderLast[numValsInt];
  int elbowLast[numValsInt];

	for(int i = 0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
    elbowLast[i] = 0;
	}

  int elbowPower;
  int shoulderPower;

  while((dist(elbowAngle(encoderElbow), elbowTarget) >= 10) || (dist(shoulderAngle(encoderShoulder), shoulderTarget) >= 10)) {

    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast, numValsInt);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast, numValsInt);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    armMove(elbowPower, shoulderPower);

    delay(opContInt);
  }

}


void FindElbowLimit(Encoder encoderElbow, Encoder encoderShoulder) {
  //use convention shoulder, elbow in pairs


  double shoulderPID[] = {0,0,0};
  double shoulderWeights[] = {5,0,0};

  double shoulderTargets[] = {0,0,0};

  int numValsInt = 50;

  int shoulderLast[numValsInt];

	for(int i = 0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
	}

    int shoulderPower;

  while(limitSwitchGetElbow() == false) {

    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast, numValsInt);

    armMove(60, pidDotProd(shoulderPID, shoulderWeights));

    delay(opContInt);
  }

}

#endif
