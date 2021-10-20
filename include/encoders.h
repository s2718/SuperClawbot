#ifndef _ENCODERS_H_
#define _ENCODERS_H_

#include "main.h"
#include "constants.h"

double elbowAngle(Encoder elbowEnc) {
  return (double)(encoderGet(elbowEnc) * elbowEncGearRatio);
}

double shoulderAngle(Encoder shoulderEnc) {
  return (double)(encoderGet(shoulderEnc) * shoulderEncGearRatio);
}

#endif

// #ifndef _ENC_
// #define _ENC_
// extern int i;
// #endif
