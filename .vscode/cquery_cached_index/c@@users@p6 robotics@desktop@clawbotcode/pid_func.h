#include "main.h"


int pid(int last[10], int target) {
  int s = 0;
  for (int i = 0; i < 10; i++) {
    s += last[i];
  }

  int integral = s * sensCollInt;

  int prop = last[9] - target;

}
