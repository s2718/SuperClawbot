#include "main.h"    // includes API.h and other headers
#include "chassis.h" // redundant, but ensures that the corresponding header file (chassis.h) is included

void chassisSet(int left, int right) {
  motorSet(2, left);
  motorSet(3, right);
}
