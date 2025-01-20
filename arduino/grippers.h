#ifndef GRIPPERS_H
#define GRIPPERS_H

#include "servo.h"

class Gripper {
  public:
    Gripper(Adafruit_PWMServoDriver &pwm, const int pin);
    Gripper(const RobotServo servo);
    void open(const bool slow = false);
    void close(const bool slow = false);

  private:
    RobotServo _servo;
};

#endif // GRIPPERS_H