#ifndef GRIPPERS_H
#define GRIPPERS_H

#include "servo.h"

class Gripper {
  public:
    Gripper(const Adafruit_PWMServoDriver pwm, int pin);
    Gripper(const RobotServo servo);
    void open();
    void close();

  private:
    RobotServo _servo;
};

#endif // GRIPPERS_H