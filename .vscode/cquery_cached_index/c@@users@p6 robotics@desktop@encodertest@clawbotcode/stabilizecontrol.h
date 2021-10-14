
#ifndef JOYSTICK_PID_CONTROL
#define JOYSTICK_PID_CONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "home.h"
#include "pid.h"

void joystickPIDContol(Encoder encoderElbow, Encoder encoderShoulder) {
  //use convention shoulder, elbow in pairs
  double elbowPID[] = {0,0,0};
  double elbowWeights[] = {15,20,5};

  double shoulderPID[] = {0,0,0};
  double shoulderWeights[] = {15,20,5};

  double elbowTargets[] = {(double)elbowAngle(encoderElbow),0,0};
  double shoulderTargets[] = {(double)shoulderAngle(encoderShoulder),0,0};

  int numValsInt = 50;

  int shoulderLast[numValsInt];
  int elbowLast[numValsInt];

	for(int i = 0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
    elbowLast[i] = 0;
	}

  int power;
  int turn;
  int wrist;
  int claw;
  int elbowPower;
  int shoulderPower;

  while (true) {
    power = joystickGetAnalog(1, 1);
    turn = -joystickGetAnalog(1, 2);
    wrist = 100 * (joystickGetDigital(1, 5, JOY_UP) - joystickGetDigital(1, 5, JOY_DOWN));
    claw = 100 * (joystickGetDigital(1, 6, JOY_UP) - joystickGetDigital(1, 6, JOY_DOWN));

    elbowTargets[0] -= joystickGetAnalog(1, 4) * 0.01;
    shoulderTargets[0] -= joystickGetAnalog(1, 3) * 0.01;

    if (elbowTargets[0] < -60) {
      elbowTargets[0] = -60;
    }

    if (elbowTargets[0] > 225) {
      elbowTargets[0] = 225;
    }

    if (elbowTargets[0] - shoulderTargets[0] > 110) {
      elbowTargets[0] = shoulderTargets[0] + 110;
    }

    if (elbowTargets[0] - shoulderTargets[0] < -230) {
      elbowTargets[0] = shoulderTargets[0] - 0;
    }


    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast, numValsInt);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast, numValsInt);

    elbowPower = -pidDotProd(elbowPID, elbowWeights);
    shoulderPower =  -pidDotProd(shoulderPID, shoulderWeights);

    chassisSet(power, turn);
    wristSet(wrist);
    clawSet(claw);
    armMove(elbowPower, shoulderPower);


    delay(opContInt);
  }

}

#endif
