#ifndef ROBOT_H
#define ROBOT_H

#include "grippers.h"
#include "hands.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

class Robot {
  public:
    Robot(Adafruit_PWMServoDriver &pwm)
        : _pwm(pwm), _lHand(Hand::getLeftHand(_pwm)),
          _rHand(Hand::getRightHand(_pwm)),
          _lGripper(Gripper::getLeftGripper(_pwm)),
          _rGripper(Gripper::getRightGripper(_pwm)) {}

    void begin() {
        _pwm.begin();
        _pwm.setOscillatorFrequency(27000000);
        _pwm.setPWMFreq(50);
    }

    void moveCube(const String move);
    void receiveCube();
    void releaseCube();

  private:
    Adafruit_PWMServoDriver &_pwm;
    Hand _lHand;
    Hand _rHand;
    Gripper _lGripper;
    Gripper _rGripper;
};

#endif