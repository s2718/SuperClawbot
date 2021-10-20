#include "main.h"

#define L1 26.5 //link 1 (shoulder) centimeters
#define L2 36.0
#define PI 3.1416
#define numValsInt 50

#define sensCollInt 20
#define opContInt 20

#define limitSwitchShoulder 4
#define limitSwitchElbow 3

#define shoulderEncGearRatio 0.6 //ratio to multiply to convert by enc ticks to joint degrees
#define elbowEncGearRatio  0.5 //ratio to multiply to convert by enc ticks to joint degrees

#define offsetShoulder 70
#define offsetElbow -92

#ifndef CONSTANTS
#define CONSTANTS

double elbowWeights[] = {10,0,0};
double shoulderWeights[] = {10,0,30};

double shoulderLast[numValsInt] = {0};
double elbowLast[numValsInt] = {0};

bool home_complete = false;

#endif
