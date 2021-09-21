#include "main.h"
#include "arm.h"
#include "limitSwitch.h"

void homeElbow(Encoder encoder) {

  for(int i = 0; i < 2; i++) {
    elbowMove(-25);
    delay(100);
    while(limitSwitchGeElbow()) {
      shoulderMove(50/(i+1));
      delay(20/(2 * i + 1));
    }
  }

  encoderReset(encoder);

  int offset = 60;
  while(encoderGet(encoder) < offset) {
    elbowMove(-25);
    delay(20);
  }


}
