#include "Arduino.h"
#include "logger.h"
#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot robot = Robot(pwm);
Logger *logger = Logger::getInstance();

void setup() {
    Serial.begin(9600);
    logger->info("Iniciando sistema...");

    robot.begin();
    logger->info("Robô inicializado");

    robot.receiveCube();
    logger->info("Cubo recebido");

    delay(10);
}

void loop() {
    String move = readString("Digite o movimento: ");
    logger->debug(("Movimento recebido: " + move).c_str());
    robot.moveCube(move);
}
