#include "grippers.h"

#define CLOSE 360
#define OPEN 460

#define SLOW_SPEED 0.02f

Gripper::Gripper(Adafruit_PWMServoDriver &pwm, const int pin)
    : _servo(RobotServo(pwm, pin, CLOSE, OPEN)) {}

Gripper::Gripper(RobotServo servo) : _servo(servo) {}

void Gripper::open(const bool slow) {
    if (slow) {
        _servo.write(OPEN, CLOSE, SLOW_SPEED);
    } else {
        _servo.write(OPEN);
    }
}

void Gripper::close(const bool slow) {
    if (slow) {
        _servo.write(CLOSE, OPEN, SLOW_SPEED);
    } else {
        _servo.write(CLOSE);
    }
}