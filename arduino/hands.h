#ifndef HANDS_H
#define HANDS_H

#include "commands.h"
#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

// Definições para a mão esquerda
#define LEFT_MAX 530
#define LEFT_MIN 130
#define LEFT_MIDDLE 320
#define LEFT_FAST_SPEED 0.1f
#define LEFT_SLOW_SPEED 0.02f
#define LEFT_HAND_PIN 14

// Definições para a mão direita
#define RIGHT_MAX 505
#define RIGHT_MIN 120
#define RIGHT_MIDDLE 320
#define RIGHT_FAST_SPEED 0.1f
#define RIGHT_SLOW_SPEED 0.02f
#define RIGHT_HAND_PIN 1

// Classe base Hand
class Hand {
  public:
    Hand(Adafruit_PWMServoDriver &pwm, const int pin, const int max,
         const int min, const int middle, const float slowSpeed,
         const float fastSpeed)
        : _servo(pwm, pin, min, max), _max(max), _min(min), _middle(middle),
          _slowSpeed(slowSpeed), _fastSpeed(fastSpeed) {}

    static Hand getLeftHand(Adafruit_PWMServoDriver &pwm) {
        return Hand(pwm, LEFT_HAND_PIN, LEFT_MAX, LEFT_MIN, LEFT_MIDDLE,
                    LEFT_SLOW_SPEED, LEFT_FAST_SPEED);
    }

    static Hand getRightHand(Adafruit_PWMServoDriver &pwm) {
        return Hand(pwm, RIGHT_HAND_PIN, RIGHT_MAX, RIGHT_MIN, RIGHT_MIDDLE,
                    RIGHT_SLOW_SPEED, RIGHT_FAST_SPEED);
    }

    // Método otimizado usando enum
    void rotate(HandDirection direction, const bool slow = false) {
        int targetPosition;
        switch (direction) {
        case HAND_DIR_CW:
            targetPosition = _max;
            break;
        case HAND_DIR_CCW:
            targetPosition = _min;
            break;
        case HAND_DIR_MID:
        default:
            targetPosition = _middle;
            break;
        }

        if (slow) {
            _servo.write(targetPosition, _slowSpeed);
        } else {
            _servo.write(targetPosition, _fastSpeed);
        }
    }

    bool isMaxPosition() { return _servo.getCurrentPosition() == _max; }
    bool isMinPosition() { return _servo.getCurrentPosition() == _min; }
    bool isMiddlePosition() { return _servo.getCurrentPosition() == _middle; }

  private:
    RobotServo _servo;
    int _max;
    int _min;
    int _middle;
    float _slowSpeed;
    float _fastSpeed;
};

#endif // HANDS_H