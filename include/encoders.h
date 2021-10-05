#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#include "main.h"

int elbowAngle(Encoder elbowEnc) {
  return (int)(encoderGet(elbowEnc) * elbowEncGearRatio);
}

int shoulderAngle(Encoder shoulderEnc) {
  return (int)(encoderGet(shoulderEnc) * shoulderEncGearRatio);
}

#endif

// #ifndef _ENC_
// #define _ENC_
// extern int i;
// #endif
