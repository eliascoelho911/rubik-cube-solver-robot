#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#define DEFAULT_DELAY 1000
#define MAX_PULSE 10000
#define MIN_PULSE 0

void Robot::receiveCube() {
    _lHand.rotate(HAND_DIR_MID);
    _rHand.rotate(HAND_DIR_MID);
    _lGripper.open();
    _rGripper.open();

    delay(2000);

    _lGripper.close(true);
    delay(20);
    _rGripper.close(true);
}

void Robot::releaseCube() {
    _lHand.rotate(HAND_DIR_MID);
    _rHand.rotate(HAND_DIR_MID);
    _lGripper.open();
    _rGripper.open();
}

void Robot::exec(Command cmd) {
    switch (cmd.type) {
    case CMD_MOVE: {
        MotorType motorType = cmd.params.moveCmd.motor;
        int pulse = cmd.params.moveCmd.pulse;
        float speed = cmd.params.moveCmd.speed;

        Serial.print(F("Movendo motor "));
        Serial.print(getMotorTypeString(motorType));
        Serial.print(F(" para pulse "));
        Serial.print(pulse);
        Serial.print(F(" com speed "));
        Serial.println(speed);

        // Verificar se é mão ou garra
        if (motorType == MOTOR_LEFT_HAND || motorType == MOTOR_RIGHT_HAND) {
            Hand *hand = nullptr;

            if (motorType == MOTOR_LEFT_HAND) {
                hand = &_lHand;
            } else {
                hand = &_rHand;
            }

            if (hand != nullptr) {
                hand->moveTo(pulse, speed);
            }
        } else if (motorType == MOTOR_LEFT_GRIPPER ||
                   motorType == MOTOR_RIGHT_GRIPPER) {
            Gripper *gripper = nullptr;

            if (motorType == MOTOR_LEFT_GRIPPER) {
                gripper = &_lGripper;
            } else {
                gripper = &_rGripper;
            }

            if (gripper != nullptr) {
                gripper->moveTo(pulse, speed);
            }
        }
        break;
    }

    case CMD_RECEIVE:
        receiveCube();
        break;

    case CMD_RELEASE:
        releaseCube();
        break;

    default:
        Serial.println(F("Comando inválido"));
        break;
    }
}
