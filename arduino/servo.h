#ifndef SERVO_H
#define SERVO_H

#include <Adafruit_PWMServoDriver.h>

class RobotServo {
  public:
    RobotServo(Adafruit_PWMServoDriver &pwm, const int pin, const int min,
               const int max);
    void write(const int pulse);
    void write(const int pulse, float speed);

    int getCurrentPosition() const;

  private:
    int _pin;
    int _min;
    int _max;
    int _currentPosition = -1;
    Adafruit_PWMServoDriver &_pwm;
};

#endif // SERVO_H