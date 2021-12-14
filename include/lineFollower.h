#include "main.h"
#include "chassis.h"
#include "arm.h"
#include "pid.h"
#include "constants.h"
#include "terminatingPIDControl.h"
#include "math.h"
#include "usefulFunctions.h"


#ifndef LINE_FOLLOWER
#define LINE_FOLLOWER


double Max(x,y) {
  if (x > y) {
    return x;
  }
  return y;
}

double Min(x,y) {
    if (x < y) {
      return x;
    }
    return y;
}



double lineWeight(position) {
  double analog = analogRead(position);

  if (analog < 200) {
    return 0;
  }

  else if (analog > 1500) {
    return 1;
  }

  else {
    return (analog - 200)/1300.0;
  }

}

bool lineDetector(position) {
  return lineWeight(position) > 0.5;
}



void lineFollower() {


  //PIDContol(encoderElbow, encoderShoulder, 0, 120);
  int initChassisPower = -50;
  int chassisPower = initChassisPower;
  int turn = 0;
  int timeSearching = 0;

  int count = 0;

  double distance = 0;// approximately centimeters

  double dDistance = 0;

  bool digitals[] = {0,0,0};


  while (!nextButton()) {
    for (int i = 1; i < 4; i ++) {
      digitals[i] = lineDetector(i);
    }

    count ++;


    if (count %10 == 0)  {
      // for (int i = 1; i < 4; i ++) {
      //   printf("%d: ",i);
      //   printf("%f\n", analogs[i]);
      // }

      printf("Distance: %f", distance);
      printf("\n");
    }

    chassisPower = initChassisPower;

    if  (digitals[0] || digitals[1] || digitals[2]) {
      timeSearching = 0;
      dDistance = 2 * (digitals[2] - digitals[1]) - distance;
      distance = 2 * (digitals[2] - digitals[1]);
      turn = -distance * 5 - 5 * dDistance;

    }

    else {
      chassisPower = 0;
      turn = -0.025 * opContInt * Max(timeSearching, 30) * distance;
      if (abs(turn) > 40) {
        turn = -20 * distance;
      }
      timeSearching += 1;

      if (turn == 0) {
        turn = -0.025 * opContInt * Max(timeSearching, 100) * sin(0.15 * opContInt * timeSearching * M_PI/180);
      }

    }



    chassisSet(chassisPower, turn);


    delay(opContInt);


  }

}




void lineFollowerUnused() {


  //PIDContol(encoderElbow, encoderShoulder, 0, 120);

  int chassisPower = 30;
  int turn = 0;
  int timeSearching = 0;

  int count = 0;

  double distance = 0;// approximately centimeters

  double latVel = 0;

  double angle = 0;

  double analogs[] =  {0,0,0};

  double deltaAnalogs[] = {0,0,0};

  bool digitals[] = {0,0,0};


  while (1) {
    for (int i = 1; i < 4; i ++) {
      deltaAnalogs[i] = (lineWeight(i) - analogs[i]) * 1000.0/opContInt;

      analogs[i] = lineWeight(i);

      digitals[i] = lineDetector(i);
    }

    count ++;


    if (count %10 == 0)  {
      // for (int i = 1; i < 4; i ++) {
      //   printf("%d: ",i);
      //   printf("%f\n", analogs[i]);
      // }

      printf("Distance: %f", distance);
      printf("latVel: %f", latVel);
      printf("\n");
    }


    if (!digitals[0] && digitals[1] && !digitals[2]) {
      distance = 0;
    }

    else if  (digitals[0] && !digitals[1] && !digitals[2]) {
      distance = -2;
      latVel = -(deltaAnalogs[0] - deltaAnalogs[1]);
    }

    else if  (!digitals[0] && !digitals[1] && digitals[2]) {
      distance = 2;
      latVel = (deltaAnalogs[2] - deltaAnalogs[1]);

    }

    else {
      distance += opContInt/1000.0 * latVel;
    }


    turn = -100 * distance - 100 * latVel;

    if (abs(turn) > chassisPower/2) {
      turn = chassisPower/2 * (turn)/abs(turn);
    }

    latVel += 0.001 *  turn * chassisPower * opContInt/1000.0;


    chassisSet(chassisPower, turn);


    delay(opContInt);


  }

}

#endif
