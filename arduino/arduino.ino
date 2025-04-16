#include "Arduino.h"
#include "logger.h"
#include "robot.h"
#include "serial.h"
#include "test_mode.h"
#include <Adafruit_PWMServoDriver.h>

#define LEFT_HAND 15
#define RIGHT_HAND 0
#define LEFT_GRIPPER 14
#define RIGHT_GRIPPER 1

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot robot = Robot(pwm, LEFT_HAND, RIGHT_HAND, LEFT_GRIPPER, RIGHT_GRIPPER);
Logger *logger = Logger::getInstance();
TestMode testMode = TestMode(robot);

void setup() {
    Serial.begin(9600);
    logger->info("Iniciando sistema...");

    robot.begin();
    logger->info("Robô inicializado");

    robot.receiveCube();
    logger->info("Cubo recebido");

    testMode.run();

    delay(10);
}

void loop() {
    String move = readString("Digite o movimento: ");
    logger->debug(("Movimento recebido: " + move).c_str());
    robot.moveCube(move);
}
