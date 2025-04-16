#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define DEFAULT_DELAY 1000
#define MAX_PULSE 10000
#define MIN_PULSE 0

void Robot::receiveCube() {
    _lHand.move(0);
    _rHand.move(0);
    _lGripper.open();
    _rGripper.open();

    Serial.println("Place the cube in the robot's");
    delay(2000);
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
