#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define SERVO_FREQ 50
#define DEFAULT_DELAY 1000
#define MAX_PULSE 10000
#define MIN_PULSE 0

Robot::Robot(Adafruit_PWMServoDriver &pwm, const int lHand, const int rHand,
             const int lGripper, const int rGripper)
    : _pwm(pwm), _lHand(LeftHand(pwm, lHand)), _rHand(RightHand(pwm, rHand)),
      _lGripper(LeftGripper(pwm, lGripper)),
      _rGripper(RightGripper(pwm, rGripper)) {}

void Robot::begin() {
    _pwm.begin();
    _pwm.setOscillatorFrequency(27000000);
    _pwm.setPWMFreq(SERVO_FREQ);
}

void Robot::receiveCube() {
    _lHand.move(0);
    _rHand.move(0);
    _lGripper.open();
    _rGripper.open();

    Serial.println("Place the cube in the robot's");
    awaitInput("Press any key to continue...");
    Serial.println("Starting to close the grippers...");

    _lGripper.close(true);
    delay(20l);
    _rGripper.close(true);

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

void Robot::moveCube(const String move) {
    if (move == "L") {
        _lGripper.close();
        _rGripper.close();
        _lHand.move(-1, true);
    } else if (move == "L'") {
        _lGripper.close();
        _rGripper.close();
        _lHand.move(1, true);
    }
}
