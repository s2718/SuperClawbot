#ifndef LINE_FOLLOWER
#define LINE_FOLLOWER


#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "constants.h"
#include "terminatingPIDControl.h"

void lineFollower(Encoder encoderElbow, Encoder encoderShoulder, Ultrasonic ultra) {


  PIDContol(encoderElbow, encoderShoulder, 0, 120);

  int ultraDistance;
  int chassisPower;

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


  clawSet(1000);
  delay(2000);
  clawSet(0);

  while (1) {
    ultraDistance = ultrasonicGet(ultra);

    chassisPower = (ultraDistance-30) * 20;
    chassisSet(chassisPower, 0);

    printf("%d\n",ultraDistance);


    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    armMove(elbowPower, shoulderPower);


    delay(opContInt);
  }

}



#endif
