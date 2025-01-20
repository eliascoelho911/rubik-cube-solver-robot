#include "hands.h"

LeftHand::LeftHand(Adafruit_PWMServoDriver &pwm, const int pin)
    : Hand(RobotServo(pwm, pin, 120, 480)) {}

void LeftHand::move(const int direction) {
    if (direction > 0) {
        _servo.write(120);
    } else if (direction < 0) {
        _servo.write(480);
    } else {
        _servo.write(300);
    }
}

RightHand::RightHand(Adafruit_PWMServoDriver &pwm, const int pin)
    : Hand(RobotServo(pwm, pin, 120, 480)) {}

void RightHand::move(const int direction) {
    if (direction > 0) {
        _servo.write(480);
    } else if (direction < 0) {
        _servo.write(120);
    } else {
        _servo.write(300);
    }
}