#ifndef SERVO_H
#define SERVO_H

#include <Adafruit_PWMServoDriver.h>

class RobotServo {
  public:
    RobotServo(Adafruit_PWMServoDriver pwm, int pin, int min, int max);
    void write(int pulse);

  private:
    int _pin;
    int _min;
    int _max;
    Adafruit_PWMServoDriver _pwm;
};

#endif // SERVO_H