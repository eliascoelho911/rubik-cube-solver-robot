#include "Arduino.h"
#include "robot/robot.h"
#include "util/serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot robot = Robot(pwm, 14, 12, 15, 13);

void setup() {
    Serial.begin(9600);
    Serial.println("Starting...");

    robot.receiveCube();

    delay(10);
}

void loop() {
    String move = readString("Digite o movimento: ");
    robot.moveCube(move);
}
