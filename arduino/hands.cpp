#include "hands.h"

#define SLOW_SPEED 0.02f

#define MAX 480
#define MIN 120
#define MIDDLE 300

LeftHand::LeftHand(Adafruit_PWMServoDriver &pwm, const int pin)
    : Hand(RobotServo(pwm, pin, MIN, MAX)) {}

void LeftHand::move(const int direction) {
    if (direction > 0) {
        _servo.write(MIN);
    } else if (direction < 0) {
        _servo.write(MAX);
    } else {
        _servo.write(MIDDLE);
    }
}

RightHand::RightHand(Adafruit_PWMServoDriver &pwm, const int pin)
    : Hand(RobotServo(pwm, pin, 120, 480)) {}

void RightHand::move(const int direction) {
    if (direction > 0) {
        _servo.write(MAX);
    } else if (direction < 0) {
        _servo.write(MIN);
    } else {
        _servo.write(MIDDLE);
    }
}