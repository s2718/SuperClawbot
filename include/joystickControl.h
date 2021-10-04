
#ifndef JOYSTICKCONTROL
#define JOYSTICKCONTROL

#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "home.h"

void joystickContol() {
  int power;
  int turn;
  int shoulder;
  int elbow;
  int wrist;
  int claw;

  while (true) {
    power = joystickGetAnalog(1, 1);
    turn = -joystickGetAnalog(1, 2);
    shoulder = -joystickGetAnalog(1, 3);
    elbow = -joystickGetAnalog(1, 4);
    wrist = 100 * (joystickGetDigital(1, 5, JOY_UP) - joystickGetDigital(1, 5, JOY_DOWN));
    claw = 100 * (joystickGetDigital(1, 6, JOY_UP) - joystickGetDigital(1, 6, JOY_DOWN));

    chassisSet(power, turn);
    wristSet(wrist);
    clawSet(claw);
    armMove(elbow, shoulder);

    delay(opContInt);
  }

}


#endif
