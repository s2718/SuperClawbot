#ifndef HOME_JOINTS
#define HOME_JOINTS

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"
#include "encoders.h"
#include "terminatingPIDControl.h"

void home(Encoder encoderElbow, Encoder encoderShoulder) {

///start home shoulder
  while(limitSwitchGetShoulder() == false) {
    armMove(0,-50);
    delay(20);
  }
  encoderReset(encoderShoulder);
  encoderReset(encoderElbow);

  int offsetShoulder = 70;
  PIDContol(encoderElbow, encoderShoulder, 0, offsetShoulder);
  encoderReset(encoderShoulder);

//end home shoulder

//home elbow
  FindElbowLimit(encoderElbow, encoderShoulder);
  encoderReset(encoderElbow);
  int offsetElbow = -125;
  PIDContol(encoderElbow, encoderShoulder, offsetElbow, 0);
  encoderReset(encoderElbow);

//end home elbow



}

#endif
