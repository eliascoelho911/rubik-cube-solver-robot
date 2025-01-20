#include "servo.h"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

RobotServo::RobotServo(Adafruit_PWMServoDriver pwm, int pin, int min, int max)
    : _pwm(pwm), _pin(pin), _min(min), _max(max) {}

void RobotServo::write(int pulse) {
    if (pulse < _min)
        pulse = _min;
    if (pulse > _max)
        pulse = _max;

    _pwm.setPWM(_pin, 0, pulse);
}