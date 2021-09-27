
#ifndef JOYSTICKCONTROL
#define JOYSTICKCONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid_func.h"
#include "home.h"

void joystickContol() {
  int power = joystickGetAnalog(1, 1);
  int turn = -joystickGetAnalog(1, 2);
  int shoulder = joystickGetAnalog(1, 3);
  int elbow =- joystickGetAnalog(1, 4);
  int wrist = 100 * (joystickGetDigital(1, 5, JOY_UP) - joystickGetDigital(1, 5, JOY_DOWN));
  int claw = 100 * (joystickGetDigital(1, 6, JOY_UP) - joystickGetDigital(1, 6, JOY_DOWN));
  // set wrist power
  // set claw power

  chassisSet(power, turn);
  wristSet(wrist);
  clawSet(claw);
  armMove(elbow, shoulder);
}

#endif
