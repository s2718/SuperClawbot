
#ifndef PID
#define PID

#include "main.h"
#include "chassis.h"
#include "arm.h"


double deriv(int last[], int delta) {
  return ((last[0] - last[delta])/((double)delta * opContInt));
}

int pidDotProd(double pid[], double weights[]) {
  double sum = 0;
  for (int i = 0; i < 3; i++) {
    sum += pid[i] * weights[i];
  }
  return (int)sum;
}

void calcNextVals(double pid[], double targets[], int measured, int last[], int lastLength) { //pid, targets is array {p,i,d}
  pid[0] = (double)measured - targets[0];
  pid[1] += 0.02 * (pid[0] - targets[1]); //reimann sum weighted by geometric distribution
  pid[2] = deriv(last, 5) - targets[2];

  for (int i = 1; i < lastLength; i++) {
    last[i] = last[i - 1];
  }
  last[0] = measured;
}

#endif
