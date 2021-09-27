#ifndef HOME_JOINTS
#define HOME_JOINTS

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"

void home(Encoder encoderShoulder, Encoder encoderElbow) {
//home elbow
  while(limitSwitchGetElbow() == false) {
    elbowMove(50);
    delay(20);
  }
  encoderReset(encoderElbow);

  int offsetElbow = - 60;
  while(encoderGet(encoderElbow) > offsetElbow) {
    elbowMove(-50);
    delay(20);
  }
  encoderReset(encoderElbow);

//end home elbow

//start home shoulder

  while(limitSwitchGetShoulder() == false) {
    shoulderMove(-50);
    delay(20);
  }
  encoderReset(encoderShoulder);

  int offsetShoulder = 60;
  while(encoderGet(encoderShoulder) < offsetShoulder) {
    shoulderMove(50);
    delay(20);
  }
//end home shoulder

}

#endif
