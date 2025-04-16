#include "grippers.h"
#include "logger.h"

// Definições específicas para a garra esquerda
#define LEFT_CLOSE 380
#define LEFT_OPEN 480
#define LEFT_SLOW_SPEED 0.02f
#define LEFT_FAST_SPEED 0.1f
// Definições específicas para a garra direita
#define RIGHT_CLOSE 370
#define RIGHT_OPEN 480
#define RIGHT_SLOW_SPEED 0.02f
#define RIGHT_FAST_SPEED 0.1f

// Implementação da garra esquerda
LeftGripper::LeftGripper(Adafruit_PWMServoDriver &pwm, const int pin)
    : _servo(RobotServo(pwm, pin, LEFT_CLOSE, LEFT_OPEN)) {}

LeftGripper::LeftGripper(const RobotServo servo) : _servo(servo) {}

void LeftGripper::open(const bool slow) {
    Logger *logger = Logger::getInstance();

    if (slow) {
        logger->debug("Abrindo garra esquerda lentamente");
        _servo.write(LEFT_OPEN, LEFT_SLOW_SPEED);
    } else {
        logger->debug("Abrindo garra esquerda rapidamente");
        _servo.write(LEFT_OPEN, LEFT_FAST_SPEED);
    }
}

void LeftGripper::close(const bool slow) {
    Logger *logger = Logger::getInstance();

    if (slow) {
        logger->debug("Fechando garra esquerda lentamente");
        _servo.write(LEFT_CLOSE, LEFT_SLOW_SPEED);
    } else {
        logger->debug("Fechando garra esquerda rapidamente");
        _servo.write(LEFT_CLOSE, LEFT_FAST_SPEED);
    }
}

// Implementação da garra direita
RightGripper::RightGripper(Adafruit_PWMServoDriver &pwm, const int pin)
    : _servo(RobotServo(pwm, pin, RIGHT_CLOSE, RIGHT_OPEN)) {}

RightGripper::RightGripper(const RobotServo servo) : _servo(servo) {}

void RightGripper::open(const bool slow) {
    Logger *logger = Logger::getInstance();

    if (slow) {
        logger->debug("Abrindo garra direita lentamente");
        _servo.write(RIGHT_OPEN, RIGHT_SLOW_SPEED);
    } else {
        logger->debug("Abrindo garra direita rapidamente");
        _servo.write(RIGHT_OPEN, RIGHT_FAST_SPEED);
    }
}

void RightGripper::close(const bool slow) {
    Logger *logger = Logger::getInstance();

    if (slow) {
        logger->debug("Fechando garra direita lentamente");
        _servo.write(RIGHT_CLOSE, RIGHT_SLOW_SPEED);
    } else {
        logger->debug("Fechando garra direita rapidamente");
        _servo.write(RIGHT_CLOSE, RIGHT_FAST_SPEED);
    }
}