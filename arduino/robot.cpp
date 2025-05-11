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

    delay(2000);

    _lGripper.close(true);
    delay(20l);
    _rGripper.close(true);
}

void Robot::releaseCube() {
    _lHand.move(0);
    _rHand.move(0);
    _lGripper.open();
    _rGripper.open();
}

void Robot::exec(String eventId, String *args) {
    if (eventId == "move") {
        for (int i = 0; i < args->length(); i++) {
            String arg = args[i];
            int motorIdIndex = arg.indexOf(",");
            String motorId = arg.substring(0, motorIdIndex);
            String movement = arg.substring(motorIdIndex + 1);

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
                if (movement == "H") {
                    // TODO: Implementar movimento horário
                } else if (movement == "H'") {
                    // TODO: Implementar movimento anti-horário
                } else if (movement == "C") {
                    // TODO: Implementar movimento para centralizar
                } else {
                    logger->error("Comando inválido");
                }
            } else if (gripper != nullptr) {
                if (movement == "open") {
                    gripper->open(true);
                } else if (movement == "close") {
                    gripper->close(true);
                } else {
                    logger->error("Comando inválido");
                }
            }
        }
    }
}
