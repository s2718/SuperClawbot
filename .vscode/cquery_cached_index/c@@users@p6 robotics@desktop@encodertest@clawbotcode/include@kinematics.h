#include "main.h"
#include "math.h"
#include "constants.h"

#ifndef KINEMATICS_H
#define KINEMATICS_H


double forward_kinematic_x(elbow, shoulder) {
  return cos(PI * shoulder/180) * L1 + cos(PI * (elbow)/180) * L2;
}

double forward_kinematic_z(elbow, shoulder) {
  return sin(PI * shoulder/180) * L1 + sin(PI * (elbow)/180) * L2;
}

double DVal(x,y) {
  return (double)(x*x + y*y - L1*L1 - L2*L2)/(2 * L1 * L2);
}

double reverse_kinematic_theta_elbow_upper(x,z) {
  double D = DVal(x,z);
  return atan(sqrt(1 - D*D)/D);
}

double reverse_kinematic_theta_elbow_lower(x,z) {
  double D = DVal(x,z);
  return -atan(sqrt(1 - D*D)/D);
}

double reverse_kinematic_theta_shoulder_lower(x,z) {
  double theta_elbow =  reverse_kinematic_theta_elbow_lower(x,z);
  return atan(z/x) + atan(L2 * sin(theta_elbow)/(L1 + L2 * cos(theta_elbow)));
}

double reverse_kinematic_theta_shoulder_upper(x,z) {
  double theta_elbow =  reverse_kinematic_theta_elbow_upper(x,z);
  return atan(z/x) + atan(L2 * sin(theta_elbow)/(L1 + L2 * cos(theta_elbow)));
}

double upperShoulder(x,z) {
  if (x*x+z*z <= L1 * L1 + L2 * L2) {
    return reverse_kinematic_theta_shoulder_upper(x,z);
  }
  else {
    return 0;
  }
}

double upperElbow(x,z) {
  if (x*x+z*z <= L1 * L1 + L2 * L2) {
    return reverse_kinematic_theta_elbow_upper(x,z) + reverse_kinematic_theta_shoulder_upper(x,z);
  }
  else {
    return 0;
  }
}


#endif
