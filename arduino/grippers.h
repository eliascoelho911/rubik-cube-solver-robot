#ifndef GRIPPERS_H
#define GRIPPERS_H

#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

// Classe base abstrata
class Gripper {
  public:
    virtual void open(const bool slow = false) = 0;
    virtual void close(const bool slow = false) = 0;
};

// Implementação da garra esquerda
class LeftGripper : public Gripper {
  public:
    LeftGripper(Adafruit_PWMServoDriver &pwm, const int pin);
    LeftGripper(const RobotServo servo);
    virtual void open(const bool slow = false) override;
    virtual void close(const bool slow = false) override;

  private:
    RobotServo _servo;
};

// Implementação da garra direita
class RightGripper : public Gripper {
  public:
    RightGripper(Adafruit_PWMServoDriver &pwm, const int pin);
    RightGripper(const RobotServo servo);
    virtual void open(const bool slow = false) override;
    virtual void close(const bool slow = false) override;

  private:
    RobotServo _servo;
};

#endif // GRIPPERS_H