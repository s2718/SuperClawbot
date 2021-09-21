#include "main.h"

bool limitSwitchGetShoulder() {
  return digitalRead(limitSwitchShoulder);
}

bool limitSwitchGeElbow() {
  return digitalRead(limitSwitchElbow);
}
