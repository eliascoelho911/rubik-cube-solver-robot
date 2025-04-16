#include "hands.h"
#include "logger.h"

// Definições para a mão esquerda
#define LEFT_MAX 520
#define LEFT_MIN 120
#define LEFT_MIDDLE 320
#define LEFT_FAST_SPEED 0.1f
#define LEFT_SLOW_SPEED 0.02f

// Definições para a mão direita
#define RIGHT_MAX 520
#define RIGHT_MIN 120
#define RIGHT_MIDDLE 320
#define RIGHT_FAST_SPEED 0.1f
#define RIGHT_SLOW_SPEED 0.02f

LeftHand::LeftHand(Adafruit_PWMServoDriver &pwm, const int pin)
    : Hand(RobotServo(pwm, pin, LEFT_MIN, LEFT_MAX)) {}

void LeftHand::move(const int direction, const bool slow) {
    int targetPosition;
    Logger *logger = Logger::getInstance();

    if (direction > 0) {
        targetPosition = LEFT_MIN;
    } else if (direction < 0) {
        targetPosition = LEFT_MAX;
    } else {
        targetPosition = LEFT_MIDDLE;
    }

    if (slow) {
        logger->debug("Mão esquerda movendo lentamente para posição %d",
                      targetPosition);
        _servo.write(targetPosition, LEFT_SLOW_SPEED);
    } else {
        logger->debug("Mão esquerda movendo rapidamente para posição %d",
                      targetPosition);
        _servo.write(targetPosition, LEFT_FAST_SPEED);
    }
}

RightHand::RightHand(Adafruit_PWMServoDriver &pwm, const int pin)
    : Hand(RobotServo(pwm, pin, RIGHT_MIN, RIGHT_MAX)) {}

void RightHand::move(const int direction, const bool slow) {
    int targetPosition;
    Logger *logger = Logger::getInstance();

    if (direction > 0) {
        targetPosition = RIGHT_MAX;
    } else if (direction < 0) {
        targetPosition = RIGHT_MIN;
    } else {
        targetPosition = RIGHT_MIDDLE;
    }

    if (slow) {
        logger->debug("Mão direita movendo lentamente para posição %d",
                      targetPosition);
        _servo.write(targetPosition, RIGHT_SLOW_SPEED);
    } else {
        logger->debug("Mão direita movendo rapidamente para posição %d",
                      targetPosition);
        _servo.write(targetPosition, RIGHT_FAST_SPEED);
    }
}