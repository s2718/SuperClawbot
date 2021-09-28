
#ifndef _ARM_H_
#define _ARM_H_

#include "main.h"
#include "limitSwitch.h"
#include "encoders.h"

void shoulderMove(shoulder) {
  motorSet(5,- shoulder);
}

void elbowMove(elbow) {
  motorSet(4,-elbow);
}

void shoulderSafetyMove(shoulder) { // moves and checks that the joint isn't pressing against the limit switch
  if(limitSwitchGetShoulder() && (shoulder < 10)) {
    shoulderMove(25);
  }
  else {
    shoulderMove(shoulder);
  }
}

void elbowSafetyMove(elbow) { // moves and checks that the joint isn't pressing against the limit switch
  if(limitSwitchGetElbow() && (elbow > -25)) {
    elbowMove(-50);
  }
  else {
    elbowMove(elbow);
  }
}

void armMove(elbow, shoulder) {
  elbowSafetyMove(elbow);
  shoulderSafetyMove(shoulder);
}

void pidElbow(int elbowTarget, Encoder elbowEnc) {
  elbowSafetyMove(5 * (elbowTarget - elbowAngle(elbowEnc)));
}

void pidShoulder(int shoulderTarget, Encoder shoulderEnc) {
  shoulderSafetyMove(15 * (shoulderTarget - shoulderAngle(shoulderEnc)));
}

void pidControl(int elbowTarget,int shoulderTarget, Encoder elbowEnc, Encoder shoulderEnc)
{
  pidElbow(elbowTarget, elbowEnc);
  pidShoulder(shoulderTarget, shoulderEnc);
}

void wristSet(wrist) {
  motorSet(3, wrist);
}

void clawSet(claw) {
  motorSet(2, claw);
}


#endif
