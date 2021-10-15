#ifndef HOME_JOINTS
#define HOME_JOINTS

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"
#include "encoders.h"
#include "terminatingPIDControl.h"
#include "constants.h"

void home(Encoder encoderElbow, Encoder encoderShoulder) {
  printf("\nstarting homing\n");
///start home shoulder
  while(limitSwitchGetShoulder() == false || limitSwitchGetElbow() == false) {
    armMove(60,-60);
    delay(opContInt);
  }
  encoderReset(encoderShoulder);
  encoderReset(encoderElbow);

  PIDContol(encoderElbow, encoderShoulder, offsetElbow, offsetShoulder);
  encoderReset(encoderShoulder);
  encoderReset(encoderElbow);

  printf("finished homing\n");

  home_complete = true;

}

#endif
