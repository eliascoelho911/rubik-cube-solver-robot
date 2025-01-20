#ifndef ROBOT_H
#define ROBOT_H

#include "grippers.h"
#include "hands.h"

class Robot {
  public:
    Robot(const Adafruit_PWMServoDriver pwm, const int lHand, const int rHand,
          const int lGripper, const int rGripper);
    void moveCube(String move);
    void receiveCube();
    void releaseCube();

  private:
    Adafruit_PWMServoDriver _pwm;
    LeftHand _lHand;
    RightHand _rHand;
    Gripper _lGripper;
    Gripper _rGripper;
};

#endif