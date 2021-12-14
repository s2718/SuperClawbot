
#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "constants.h"
#include "terminatingPIDControl.h"
#include "math.h"
#include "usefulFunctions.h"


#ifndef PATH_FOLLOWER
#define PATH_FOLLOWER

double max(x,y) {
  if (x > y) {
    return x;
  }
  return y;
}


void ultrasonicFollower(Encoder encoderElbow, Encoder encoderShoulder, Ultrasonic ultra) {

  PIDContol(encoderElbow, encoderShoulder, 0, 120);

  int ultraDistance;
  int chassisPower;
  int turn;
  int timeSearching = 0;

  int count = 0;

  double elbowPID[] = {0,0,0};

  double shoulderPID[] = {0,0,0};

  double elbowTargets[] = {0,0,0};
  double shoulderTargets[] = {120,0,0};

	for(int i = 0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
    elbowLast[i] = 0;
	}

  int elbowPower;
  int shoulderPower;


  clawSet(1000);
  delay(2000);
  clawSet(0);

  ultraDistance = ultrasonicGet(ultra);

  while (!nextButton()) {
    count ++;

    ultraDistance = ultrasonicGet(ultra);

    if (count %10 == 0)
    {
      printf("%d\n",ultraDistance);
    }


    if (ultraDistance > 0 && ultraDistance < 75 ) {
      timeSearching = 0;
      turn = 0;
      chassisPower = (ultraDistance - 40) * 2;
    }

    else {

      chassisPower = 0;
      turn = 0.025 * opContInt * max(timeSearching, 100) * sin(0.1 * opContInt * timeSearching * M_PI/180);
      timeSearching += 1;
    }

    chassisSet(chassisPower, turn);


    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    armMove(elbowPower, shoulderPower);




    delay(opContInt);


  }

}

void straightLineFollower(Encoder encoderElbow, Encoder encoderShoulder, Ultrasonic ultra) {


  //PIDContol(encoderElbow, encoderShoulder, 0, 120);

  int ultraDistance;
  int chassisPower;

  int count = 0;

  double elbowPID[] = {0,0,0};

  double shoulderPID[] = {0,0,0};

  double elbowTargets[] = {0,0,0};
  double shoulderTargets[] = {120,0,0};

	for(int i = 0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
    elbowLast[i] = 0;
	}

  int elbowPower;
  int shoulderPower;


  clawSet(1000);
  delay(2000);
  clawSet(0);

  while (1) {
    ultraDistance = ultrasonicGet(ultra);

    if (ultraDistance != -1) {
      chassisPower = (ultraDistance - 50) * 2;
    }

    else {
        chassisPower = 0;
    }

    chassisSet(chassisPower, 0);


    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    //armMove(elbowPower, shoulderPower);


    if (count %100 == 0)
    {
      printf("%d\n",ultraDistance);
    }

    delay(opContInt);


  }

}



#endif
