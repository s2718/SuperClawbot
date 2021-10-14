#ifndef HOME_JOINTS
#define HOME_JOINTS

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"
#include "encoders.h"
#include "terminatingPIDControl.h"
#include "constants.h"

void home(Encoder encoderElbow, Encoder encoderShoulder) {
  printf("\nstarting homing shoulder\n");
///start home shoulder
  while(limitSwitchGetShoulder() == false) {
    armMove(0,-50);
    delay(opContInt);
  }
  encoderReset(encoderShoulder);
  encoderReset(encoderElbow);

  PIDContol(encoderElbow, encoderShoulder, 0, offsetShoulder);
  encoderReset(encoderShoulder);

//end home shoulder
  printf("finished homing shoulder, starting elbow \n");
//home elbow
  FindElbowLimit(encoderElbow, encoderShoulder);
  encoderReset(encoderElbow);

  printf("elbow limit found\n");
  PIDContol(encoderElbow, encoderShoulder, offsetElbow, 0);
  encoderReset(encoderElbow);

//end home elbow
  printf("homing complete\n");
  printf("shoulder: %d\n", shoulderAngle(encoderShoulder));
  printf("elbow: %d\n", elbowAngle(encoderElbow));



}

#endif
