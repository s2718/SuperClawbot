
#ifndef JOYSTICK_PID_CONTROL
#define JOYSTICK_PID_CONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "constants.h"

void joystickPIDContol(Encoder encoderElbow, Encoder encoderShoulder) {

  double elbowPID[] = {0,0,0};

  double shoulderPID[] = {0,0,0};

  double elbowTargets[] = {(double)elbowAngle(encoderElbow),0,0};
  double shoulderTargets[] = {(double)shoulderAngle(encoderShoulder),0,0};

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

    elbowTargets[0] -= joystickGetAnalog(1, 4) * 0.005;
    shoulderTargets[0] -= joystickGetAnalog(1, 3) * 0.005;

    checkSafePositions(elbowTargets, shoulderTargets);

    calcNextVals(elbowPID, elbowTargets, elbowAngle(encoderElbow), elbowLast);
    calcNextVals(shoulderPID, shoulderTargets, shoulderAngle(encoderShoulder), shoulderLast);

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
