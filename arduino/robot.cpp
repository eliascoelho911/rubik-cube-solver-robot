#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define DEFAULT_DELAY 1000
#define MAX_PULSE 10000
#define MIN_PULSE 0

void Robot::receiveCube() {
    _lHand.rotate("mid");
    _rHand.rotate("mid");
    _lGripper.open();
    _rGripper.open();

    delay(2000);

    _lGripper.close(true);
    delay(20l);
    _rGripper.close(true);
}

void Robot::releaseCube() {
    _lHand.rotate("mid");
    _rHand.rotate("mid");
    _lGripper.open();
    _rGripper.open();
}

void Robot::exec(String eventId, String *args) {
    if (eventId == "move") {
        String motorId = args[0];
        String movement = args[1];

        motorId.trim();
        movement.trim();

        Hand *hand = nullptr;
        Gripper *gripper = nullptr;
        if (motorId == "hl") {
            hand = &_lHand;
        } else if (motorId == "hr") {
            hand = &_rHand;
        } else if (motorId == "gl") {
            gripper = &_lGripper;
        } else if (motorId == "gr") {
            gripper = &_rGripper;
        }
        if (hand != nullptr) {
            Serial.println("Movendo mão " + motorId + " para " + movement);
            hand->rotate(movement, true);
        } else if (gripper != nullptr) {
            if (movement == "open") {
                gripper->open(true);
            } else if (movement == "close") {
                gripper->close(true);
            } else {
                Serial.println("Movimento de garra inválido: " + movement);
            }
        }
    } else if (eventId == "receive") {
        receiveCube();
    } else if (eventId == "release") {
        releaseCube();
    } else {
        Serial.println("Comando com evento " + eventId + " inválido");
    }
    delete[] args;
    args = nullptr;
}
