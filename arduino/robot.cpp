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
            
            // Verificar se é mão ou garra
            if (motorType == MOTOR_LEFT_HAND || motorType == MOTOR_RIGHT_HAND) {
                Hand* hand = nullptr;
                
                if (motorType == MOTOR_LEFT_HAND) {
                    hand = &_lHand;
                    Serial.print(F("Movendo mão esquerda para "));
                } else {
                    hand = &_rHand;
                    Serial.print(F("Movendo mão direita para "));
                }
                
                HandDirection dir = cmd.params.moveCmd.handDir;
                Serial.println(getHandDirectionString(dir));
                
                if (hand != nullptr) {
                    hand->rotate(dir, true);
                }
            }
            else if (motorType == MOTOR_LEFT_GRIPPER || motorType == MOTOR_RIGHT_GRIPPER) {
                Gripper* gripper = nullptr;
                
                if (motorType == MOTOR_LEFT_GRIPPER) {
                    gripper = &_lGripper;
                    Serial.print(F("Movendo garra esquerda para "));
                } else {
                    gripper = &_rGripper;
                    Serial.print(F("Movendo garra direita para "));
                }
                
                GripperAction action = cmd.params.moveCmd.gripperAction;
                Serial.println(getGripperActionString(action));
                
                if (gripper != nullptr) {
                    if (action == GRIPPER_OPEN) {
                        gripper->open(true);
                    } else if (action == GRIPPER_CLOSE) {
                        gripper->close(true);
                    } else {
                        Serial.println(F("Movimento de garra inválido"));
                    }
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
