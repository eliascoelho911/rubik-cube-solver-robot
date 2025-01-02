#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define SERVO_CHANNEL 1
#define SERVO_FREQ 50
#define SERVO_MIN_PULSE 70
#define SERVO_MAX_PULSE 520

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando o robô resolutor de cubo mágico...");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);
}

void loop() {}
