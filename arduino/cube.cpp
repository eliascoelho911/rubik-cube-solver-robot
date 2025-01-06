#include "cube.h"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define SERVO_FREQ 50
#define DEFAULT_DELAY 1000

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

Cube::Cube() {}

void Cube::setup(int leftHandPin, int rightHandPin, int leftGripperPin,
                 int rightGripperPin) {
    this->leftHandPin = leftHandPin;
    this->rightHandPin = rightHandPin;
    this->leftGripperPin = leftGripperPin;
    this->rightGripperPin = rightGripperPin;

    Serial.println("Iniciando cubo...");
    Serial.println("Mão esquerda: " + leftHandPin);
    Serial.println("Mão direita: " + rightHandPin);
    Serial.println("Garra esquerda: " + leftGripperPin);
    Serial.println("Garra direita: " + rightGripperPin);

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);
}

void Cube::idle() {
    Serial.println("Movendo para a posição inicial...");
    moveLeftHand(MIDDLE);
    moveRightHand(MIDDLE);
    moveLeftGripper(false);
    moveRightGripper(false);
}

void Cube::moveCube(CubeMovement move) {
    if (move == L) {
        moveLeftGripper(true);
        moveRightGripper(true);
        moveLeftHand(RIGHT);
    } else if (move == L_PRIME) {
        moveLeftGripper(true);
        moveRightGripper(true);
        moveLeftHand(LEFT);
    } else if (move == R) {
        moveLeftGripper(true);
        moveRightGripper(true);
        moveRightHand(LEFT);
    } else if (move == R_PRIME) {
        moveLeftGripper(true);
        moveRightGripper(true);
        moveRightHand(RIGHT);
    } else {
        idle();
    }
}

#define LEFT_HAND_SERVO_RIGHT_PULSE 480
#define LEFT_HAND_SERVO_MIDDLE_PULSE 300
#define LEFT_HAND_SERVO_LEFT_PULSE 120

void Cube::moveLeftHand(HandPosition pos) {
    Serial.println("Movendo mão esquerda para " + String(pos));

    int pulse;

    if (pos == RIGHT) {
        pulse = LEFT_HAND_SERVO_RIGHT_PULSE;
    } else if (pos == LEFT) {
        pulse = LEFT_HAND_SERVO_LEFT_PULSE;
    } else {
        pulse = LEFT_HAND_SERVO_MIDDLE_PULSE;
    }

    pwm.setPWM(leftHandPin, 0, pulse);
    delay(DEFAULT_DELAY);
}

#define RIGHT_HAND_SERVO_RIGHT_PULSE 120
#define RIGHT_HAND_SERVO_MIDDLE_PULSE 300
#define RIGHT_HAND_SERVO_LEFT_PULSE 480

void Cube::moveRightHand(HandPosition pos) {
    Serial.println("Movendo mão direita para " + String(pos));

    int pulse;

    if (pos == RIGHT) {
        pulse = RIGHT_HAND_SERVO_RIGHT_PULSE;
    } else if (pos == LEFT) {
        pulse = RIGHT_HAND_SERVO_LEFT_PULSE;
    } else {
        pulse = RIGHT_HAND_SERVO_MIDDLE_PULSE;
    }

    pwm.setPWM(rightHandPin, 0, pulse);
    delay(DEFAULT_DELAY);
}

#define LEFT_GRIPPER_SERVO_OPEN_PULSE 460
#define LEFT_GRIPPER_SERVO_CLOSED_PULSE 395

void Cube::moveLeftGripper(bool open) {
    Serial.println("Movendo garra esquerda para aberto: " + String(open));

    int pulse =
        open ? LEFT_GRIPPER_SERVO_OPEN_PULSE : LEFT_GRIPPER_SERVO_CLOSED_PULSE;
    pwm.setPWM(leftGripperPin, 0, pulse);
    delay(DEFAULT_DELAY);
}

#define RIGHT_GRIPPER_SERVO_OPEN_PULSE 460
#define RIGHT_GRIPPER_SERVO_CLOSED_PULSE 395

void Cube::moveRightGripper(bool open) {
    Serial.println("Movendo garra direita para aberto: " + String(open));

    int pulse = open ? RIGHT_GRIPPER_SERVO_OPEN_PULSE
                     : RIGHT_GRIPPER_SERVO_CLOSED_PULSE;
    pwm.setPWM(rightGripperPin, 0, pulse);
    delay(DEFAULT_DELAY);
}
