#include "servo.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>

RobotServo::RobotServo(Adafruit_PWMServoDriver &pwm, const int pin,
                       const int min, const int max)
    : _pwm(pwm), _pin(pin), _min(min), _max(max), _currentPosition(-1) {}

void RobotServo::write(const int pulse) {
    if (pulse < _min) {
        _pwm.setPWM(_pin, 0, _min);
        _currentPosition = _min;
        return;
    } else if (pulse > _max) {
        _pwm.setPWM(_pin, 0, _max);
        _currentPosition = _max;
        return;
    }
    _pwm.setPWM(_pin, 0, pulse);
    _currentPosition = pulse;
}

void RobotServo::write(const int pulse, float speed) {
    if (speed > 1) {
        speed = 1;
    } else if (speed < 0) {
        speed = 0;
    }

    float currentPulse = _currentPosition;

    if (currentPulse == -1) {
        write(pulse);
        return;
    }

    int diff = pulse - currentPulse;
    int direction = diff > 0 ? 1 : -1;
    float step = diff * speed;
    int steps = abs(diff) / abs(step) + 1;

    for (int i = 0; i < steps; i++) {
        currentPulse += step;
        write(currentPulse);
        delay(50);
    }
}

int RobotServo::getCurrentPosition() const { return _currentPosition; }