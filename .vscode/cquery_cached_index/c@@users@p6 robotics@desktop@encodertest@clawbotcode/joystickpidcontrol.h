
void joystickPIDContol(Encoder encoderElbow, Encoder encoderShoulder) {
  int shoulderTarget = shoulderAngle(encoderShoulder);
  int elbowTarget = elbowAngle(encoderElbow);

  int elbowInt = 0; //riemann sum  of the error term weighted by a geometric distribution
  int elbowDeriv = 0;
  int shoulderInt = 0;
  int shoulderDeriv = 0; //derivative of error

  int elbowVal;
  int shoulderVal;

  int shoulderProp; //proportion error erm
  int elbowProp;

  int shoulderPower;
  int elbowPower;

  int power;
  int turn;
  int wrist;
  int claw;

  int numValsInt = 50;

  int shoulderLast[numValsInt];
  int elbowLast[numValsInt];

	for(int i =0; i < numValsInt; i++) {
		shoulderLast[i] = 0;
    elbowLast[i] = 0;
	}

  // set wrist power
  // set claw power

  while (true) {
    power = joystickGetAnalog(1, 1);
    turn = -joystickGetAnalog(1, 2);
    wrist = 100 * (joystickGetDigital(1, 5, JOY_UP) - joystickGetDigital(1, 5, JOY_DOWN));
    claw = 100 * (joystickGetDigital(1, 6, JOY_UP) - joystickGetDigital(1, 6, JOY_DOWN));

    shoulderTarget -= joystickGetAnalog(1, 3)/5;
    elbowTarget -= joystickGetAnalog(1, 4)/5;

    shoulderVal = shoulderAngle(encoderShoulder);
    elbowVal = shoulderAngle(encoderShoulder);

    shoulderProp = shoulderVal - shoulderTarget;
    elbowProp = shoulderVal - shoulderTarget;

    shoulderInt = (int) 0.98 * shoulderInt + 0.02 * shoulderProp;
    elbowInt = (int) 0.98 * elbowInt + 0.02 * elbowProp;

    for (int i = 0; i < numValsInt - 1; i++) {
      shoulderLast[i] = shoulderLast[i + 1];
      elbowLast[i] = elbowLast[i + 1];
    }

    shoulderLast[numValsInt - 1] = shoulderProp;
    elbowLast[numValsInt - 1] = elbowProp;

    #define deltaDeriv 5
    shoulderDeriv = (int)((shoulderLast[numValsInt - 1] - shoulderLast[numValsInt - 1 - deltaDeriv])/(deltaDeriv * opContInt)); //longer interval than necessary to smooth errors
    elbowDeriv = (int)((elbowLast[numValsInt - 1] - elbowLast[numValsInt - 1 - deltaDeriv])/(deltaDeriv * opContInt));

    shoulderPower = -()

    chassisSet(power, turn);
    wristSet(wrist);
    clawSet(claw);


    delay(opContInt);
  }

}
