#ifndef GRIPPERS_H
#define GRIPPERS_H

#include "commands.h"
#include "servo.h"
#include <Adafruit_PWMServoDriver.h>

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

    // Estas funções foram mantidas para compatibilidade com o código existente
    void open(const bool slow = false) {
        if (slow) {
            _servo.write(_open, _slowSpeed);
        } else {
            _servo.write(_open, _fastSpeed);
        }
    }

    void close(const bool slow = false) {
        if (slow) {
            _servo.write(_close, _slowSpeed);
        } else {
            _servo.write(_close, _fastSpeed);
        }
    }

    // Função otimizada que usa enum
    void move(GripperAction action, const bool slow = false) {
        int targetPosition;
        
        switch (action) {
            case GRIPPER_OPEN:
                targetPosition = _open;
                break;
            case GRIPPER_CLOSE:
                targetPosition = _close;
                break;
            default:
                return; // Ação inválida
        }
        
        if (slow) {
            _servo.write(targetPosition, _slowSpeed);
        } else {
            _servo.write(targetPosition, _fastSpeed);
        }
    }

  private:
    RobotServo _servo;
    int _open;
    int _close;
    float _slowSpeed;
    float _fastSpeed;
};

#endif // GRIPPERS_H