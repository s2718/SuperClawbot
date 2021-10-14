#ifndef _LIMIT_SWITCH_
#define _LIMIT_SWITCH_

#include "main.h"
#include "constants.h"


bool limitSwitchGetShoulder() {
  return ! digitalRead(limitSwitchShoulder);
}

bool limitSwitchGetElbow() {
  return ! digitalRead(limitSwitchElbow);
}

#endif
