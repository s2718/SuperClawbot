
#ifndef JOYSTICK_PID_CONTROL
#define JOYSTICK_PID_CONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "home.h"

double deriv(int last[], int delta) {
  return ((last[0] - last[delta])/((double)delta * opContInt));
}

int pidDotProd(double pid[], int weights[]) {
  double sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += pid[i] * weights[i];
  }
  return (int)sum;
}

void calcNextVals(double pid[], double targets[], int measured, int last[], int lastLength) { //pid, targets is array {p,i,d}
  pid[0] = (double)measured - targets[0];
  pid[1] = 0.98 * pid[1] + 0.02 * pid[0] - targets[1]; //reimann sum weighted by geometric distribution
  pid[2] = deriv(last, 5) - targets[2];

  for (int i = 1; i < lastLength; i++) {
    last[i] = last[i - 1];
  }
  last[0] = measured;
}

void joystickPIDContol(Encoder encoderElbow, Encoder encoderShoulder) {
  //use convention shoulder, elbow in pairs
  double elbowPID[] = {0,0,0};
  int elbowWeights[] = {15,1,1};

  double shoulderPID[] = {0,0,0};
  int shoulderWeights[] = {5,1,1};

  double elbowTargets[] = {(double)elbowAngle(encoderElbow),0,0};
  double shoulderTargets[] = {(double)shoulderAngle(encoderShoulder),0,0};

  int numValsInt = 50;

  int shoulderLast[numValsInt];
  int elbowLast[numValsInt];

	for(int i =0; i < numValsInt; i++) {
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
