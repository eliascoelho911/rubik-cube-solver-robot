#ifndef HANDS_H
#define HANDS_H

#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

// Definições para a mão esquerda
#define LEFT_MAX 520
#define LEFT_MIN 120
#define LEFT_MIDDLE 320
#define LEFT_FAST_SPEED 0.1f
#define LEFT_SLOW_SPEED 0.02f
#define LEFT_HAND_PIN 15

// Definições para a mão direita
#define RIGHT_MAX 520
#define RIGHT_MIN 120
#define RIGHT_MIDDLE 320
#define RIGHT_FAST_SPEED 0.1f
#define RIGHT_SLOW_SPEED 0.02f
#define RIGHT_HAND_PIN 0

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

    void move(const int direction, const bool slow = false) {
        int targetPosition;
        if (direction > 0) {
            targetPosition = _min;
        } else if (direction < 0) {
            targetPosition = _max;
        } else {
            targetPosition = _middle;
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