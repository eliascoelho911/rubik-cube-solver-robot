#ifndef HANDS_H
#define HANDS_H

#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

// Classe base Hand
class Hand {
  protected:
    RobotServo _servo;

  public:
    Hand(const RobotServo servo) : _servo(servo) {}
    virtual void move(const int direction, const bool slow = false) = 0;
};

// Implementação específica para mão esquerda
class LeftHand : public Hand {
  public:
    LeftHand(Adafruit_PWMServoDriver &pwm, const int pin);
    void move(const int direction, const bool slow = false) override;
};

// Implementação específica para mão direita
class RightHand : public Hand {
  public:
    RightHand(Adafruit_PWMServoDriver &pwm, const int pin);
    void move(const int direction, const bool slow = false) override;
};

#endif // HANDS_H