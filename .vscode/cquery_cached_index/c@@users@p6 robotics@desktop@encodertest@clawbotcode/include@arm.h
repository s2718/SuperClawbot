
#ifndef _ARM_H_
#define _ARM_H_

#include "main.h"
#include "limitSwitch.h"

void shoulderMove(shoulder) {
  motorSet(5,- shoulder);
}

void elbowMove(elbow) {
  motorSet(4,-elbow);
}

void armMove(elbow, shoulder) {
  if(limitSwitchGetElbow() && (elbow > -25)) {
    elbowMove(-50);
  }
  else {
    elbowMove(elbow);
  }

  if(limitSwitchGetShoulder() && (shoulder > -10)) {
    shoulderMove(-25);
  }
  else {
    shoulderMove(shoulder);
  }

}

void pidControl(int elbowTarget,int shoulderTarget, Encoder elbowEnc, Encoder shoulderEnc)
{
  armMove(5 * (elbowTarget - encoderGet(elbowEnc)), 15 * (shoulderTarget - encoderGet(shoulderEnc)));
}

void wristSet(wrist) {
  motorSet(3, wrist);
}

void clawSet(claw) {
  motorSet(2, claw);
}


#endif // _CHASSIS_H_
