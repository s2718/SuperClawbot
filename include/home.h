#ifndef HOME_JOINTS
#define HOME_JOINTS

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"

void home(Encoder encoderShoulder, Encoder encoderElbow) {

///start home shoulder
  while(limitSwitchGetShoulder() == false) {
    armMove(0,-50);
    delay(20);
  }
  encoderReset(encoderShoulder);

  int offsetShoulder = 120;
  while(encoderGet(encoderShoulder) < offsetShoulder) {
    shoulderMove(50);
    delay(20);
  }
//end home shoulder

//home elbow
  while(limitSwitchGetElbow() == false) {
    armMove(50,0);
    delay(20);
  }
  encoderReset(encoderElbow);

  int offsetElbow = - 150;
  while(encoderGet(encoderElbow) > offsetElbow) {
    elbowMove(-50);
    delay(20);
  }
  encoderReset(encoderElbow);

//end home elbow



}

#endif
