#include "main.h"

#ifndef UTILITY
#define UTILITY

bool nextButton() {
  return joystickGetDigital(1,7, JOY_LEFT);
}

void waitForButton() {
  while (!nextButton()) {
		delay(20);
	}
}


#endif
