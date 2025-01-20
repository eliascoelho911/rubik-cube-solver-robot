#ifndef SERVO_H
#define SERVO_H

#include <Adafruit_PWMServoDriver.h>

class RobotServo {
  public:
    RobotServo(const Adafruit_PWMServoDriver &pwm, const int pin, const int min,
               const int max);
    void write(const int pulse);

  private:
    int _pin;
    int _min;
    int _max;
    Adafruit_PWMServoDriver _pwm;
};

#endif // SERVO_H