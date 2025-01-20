#include "grippers.h"

Gripper::Gripper(const Adafruit_PWMServoDriver &pwm, const int pin)
    : _servo(RobotServo(pwm, pin, 395, 460)) {}

Gripper::Gripper(const RobotServo servo) : _servo(servo) {}

void Gripper::open() { _servo.write(460); }

void Gripper::close() { _servo.write(395); }