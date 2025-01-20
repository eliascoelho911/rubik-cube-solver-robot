#ifndef HANDS_H
#define HANDS_H

#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

class Hand {
  public:
    Hand(const RobotServo servo) : _servo(servo) {};
    virtual void move(const int direction) = 0;

  protected:
    RobotServo _servo;
};

class LeftHand : public Hand {
  public:
    LeftHand(const Adafruit_PWMServoDriver pwm, const int pin);
    void move(const int direction);
};

class RightHand : public Hand {
  public:
    RightHand(const Adafruit_PWMServoDriver pwm, const int pin);
    void move(const int direction);
};

#endif // HANDS_H