
#ifndef _PID_
#define _PID_

#include "main.h"


int pid(int last[10], int target) {
  int s = 0;
  for (int i = 0; i < 10; i++) {
    s += last[i];
  }

  float integral = (float)s * sensCollInt;

  float prop = (float)last[9] - target;

  float deriv = (last[9] - last[8])/ (float)sensCollInt;

  return  (int)(-prop - deriv - integral/100);

}


#endif
