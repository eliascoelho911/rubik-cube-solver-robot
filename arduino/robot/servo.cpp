#include "servo.h"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

RobotServo::RobotServo(const Adafruit_PWMServoDriver &pwm, const int pin,
                       const int min, const int max)
    : _pwm(pwm), _pin(pin), _min(min), _max(max) {}

void RobotServo::write(const int pulse) {
    if (pulse < _min) {
        _pwm.setPWM(_pin, 0, _min);
        return;
    }
    if (pulse > _max) {
        _pwm.setPWM(_pin, 0, _max);
        return;
    }

    _pwm.setPWM(_pin, 0, pulse);
}