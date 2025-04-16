#ifndef ROBOT_H
#define ROBOT_H

#include "grippers.h"
#include "hands.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

class Robot {
  public:
    Robot(Adafruit_PWMServoDriver &pwm, const int lHand, const int rHand,
          const int lGripper, const int rGripper);
    void begin();
    void moveCube(const String move);
    void receiveCube();
    void releaseCube();

    LeftHand _lHand;
    RightHand _rHand;
    LeftGripper _lGripper;
    RightGripper _rGripper;

  private:
    Adafruit_PWMServoDriver &_pwm;
};

#endif