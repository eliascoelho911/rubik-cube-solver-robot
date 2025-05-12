#ifndef GRIPPERS_H
#define GRIPPERS_H

// Definições específicas para a garra esquerda
#define LEFT_CLOSE 380
#define LEFT_OPEN 480
#define LEFT_SLOW_SPEED 0.02f
#define LEFT_FAST_SPEED 0.1f
#define LEFT_GRIPPER_PIN 15

// Definições específicas para a garra direita
#define RIGHT_CLOSE 370
#define RIGHT_OPEN 480
#define RIGHT_SLOW_SPEED 0.02f
#define RIGHT_FAST_SPEED 0.1f
#define RIGHT_GRIPPER_PIN 0

#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

class Gripper {
  public:
    Gripper(Adafruit_PWMServoDriver &pwm, const int pin, const int open,
            const int close, const float slowSpeed, const float fastSpeed)
        : _servo(RobotServo(pwm, pin, close, open)), _open(open), _close(close),
          _slowSpeed(slowSpeed), _fastSpeed(fastSpeed) {}

    static Gripper getLeftGripper(Adafruit_PWMServoDriver &pwm) {
        return Gripper(pwm, LEFT_GRIPPER_PIN, LEFT_OPEN, LEFT_CLOSE,
                       LEFT_SLOW_SPEED, LEFT_FAST_SPEED);
    }

    static Gripper getRightGripper(Adafruit_PWMServoDriver &pwm) {
        return Gripper(pwm, RIGHT_GRIPPER_PIN, RIGHT_OPEN, RIGHT_CLOSE,
                       RIGHT_SLOW_SPEED, RIGHT_FAST_SPEED);
    }

    void open(const bool slow = false) {
        if (slow) {
            _servo.write(LEFT_OPEN, LEFT_SLOW_SPEED);
        } else {
            _servo.write(LEFT_OPEN, LEFT_FAST_SPEED);
        }
    }

    void close(const bool slow = false) {
        if (slow) {
            _servo.write(LEFT_CLOSE, LEFT_SLOW_SPEED);
        }
    };

  private:
    RobotServo _servo;
    int _open;
    int _close;
    float _slowSpeed;
    float _fastSpeed;
};

#endif // GRIPPERS_H