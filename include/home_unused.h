#ifndef HOME_JOINTS_UNUSED
#define HOME_JOINTS_UNUSED

#include "main.h"
#include "arm.h"
#include "limitSwitch.h"
#include "encoders.h"
#include "terminatingPIDControl.h"
#include "constants.h"

void home_unused(Encoder encoderElbow, Encoder encoderShoulder) {
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
  // FindElbowLimit(encoderElbow, encoderShoulder);
  encoderReset(encoderElbow);

  printf("elbow limit found\n");
  PIDContol(encoderElbow, encoderShoulder, offsetElbow, 0);
  encoderReset(encoderElbow);

//end home elbow
  printf("homing complete\n");
  printf("shoulder: %f\n", shoulderAngle(encoderShoulder));
  printf("elbow: %f\n", elbowAngle(encoderElbow));

  home_complete = true;

}

#endif
