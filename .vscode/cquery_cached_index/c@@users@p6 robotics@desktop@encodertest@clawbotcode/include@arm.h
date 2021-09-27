
#ifndef _ARM_H_
#define _ARM_H_

#include "main.h"
#include "limitSwitch.h"

void shoulderMove(shoulder) {
  motorSet(5, shoulder);
}

void elbowMove(elbow) {
  motorSet(4,-elbow);
}

void armMove(elbow, shoulder) {
  if(limitSwitchGetElbow()) {
    elbowMove(-50);
  }
  else {
    elbowMove(elbow);
  }

  if(limitSwitchGetShoulder()) {
    shoulderMove(-25);
  }
  else {
    shoulderMove(shoulder);
  }

}

void wristSet(wrist) {
  motorSet(3, wrist);
}

void clawSet(claw) {
  motorSet(2, claw);
}


#endif // _CHASSIS_H_
