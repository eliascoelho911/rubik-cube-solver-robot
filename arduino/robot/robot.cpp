#include "robot.h"
#include "../util/serial.h"
#include <Adafruit_PWMServoDriver.h>

#define SERVO_FREQ 50
#define DEFAULT_DELAY 1000
#define MAX_PULSE 10000
#define MIN_PULSE 0

Robot::Robot(const Adafruit_PWMServoDriver pwm, const int lHand,
             const int rHand, const int lGripper, const int rGripper)
    : _lHand(LeftHand(pwm, lHand)), _rHand(RightHand(pwm, rHand)),
      _lGripper(Gripper(pwm, lGripper)), _rGripper(Gripper(pwm, rGripper)) {}

void Robot::receiveCube() {
    _lHand.move(0);
    _rHand.move(0);
    _lGripper.open();
    _rGripper.open();
    awaitInput("Place the cube in the robot's hands and press any key to "
               "continue...");

    _lGripper.close();
    _rGripper.close();

    Serial.println("Cube positioned!");
}

void Robot::releaseCube() {
    _lHand.move(0);
    _rHand.move(0);
    awaitInput("Hold the cube and press any key to release it...");
    _lGripper.open();
    _rGripper.open();

    Serial.println("Cube released!");
}

void Robot::moveCube(String move) {}
