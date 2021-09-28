#ifndef HOME_JOINTS
#define HOME_JOINTS

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"
#include "encoders.h"

void home(Encoder encoderShoulder, Encoder encoderElbow) {

///start home shoulder
  while(limitSwitchGetShoulder() == false) {
    armMove(0,-50);
    delay(20);
  }
  encoderReset(encoderShoulder);

  int offsetShoulder = 65;
  while(shoulderAngle(encoderShoulder) < offsetShoulder  - 3) {
    pidShoulder(offsetShoulder,encoderShoulder);
    delay(20);
  }
  encoderReset(encoderShoulder);

//end home shoulder

//home elbow
  while(limitSwitchGetElbow() == false) {
    elbowSafetyMove(30);
    pidShoulder(0,encoderShoulder);
    delay(20);
  }
  encoderReset(encoderElbow);

  int offsetElbow = - 130;
  while(elbowAngle(encoderElbow) > offsetElbow) {
    pidControl(offsetElbow, 0, encoderElbow, encoderShoulder);
    delay(20);
  }
  encoderReset(encoderElbow);

//end home elbow



}

#endif
