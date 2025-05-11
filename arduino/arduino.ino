#include "Arduino.h"
#include "HC05.h"
#include "logger.h"
#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot robot = Robot(pwm);
Logger *logger = Logger::getInstance();
HC05 bt(3, 2, 9600);

bool isConnected = false;

void setup() {
    Serial.begin(9600);
    logger->info("Iniciando sistema...");

    robot.begin();
    logger->info("Robô inicializado");

    bt.begin();
    logger->info("Bluetooth inicializado");
    logger->info("Aguardando conexão Bluetooth...");

    delay(10);
}

void loop() {
    if (bt.available()) {
        if (!isConnected) {
            logger->info("Conexão Bluetooth estabelecida");
        }

        isConnected = true;

        String command = bt.readString('\n');
        command.trim();
        command.toUpperCase();

        if (command.length() == 0) {
            return;
        }

        int separatorIndex = command.indexOf('_');
        String eventId = getEventId(command, separatorIndex);
        String *args = getArgs(command, separatorIndex);

        robot.exec(eventId, args);
    }

    delay(200);
}

String getEventId(String command, int separatorIndex) {
    if (separatorIndex < 0) {
        return "";
    }
    return command.substring(0, separatorIndex);
}

String *getArgs(String command, int separatorIndex) {
    if (separatorIndex < 0 || separatorIndex >= command.length() - 1) {
        String *emptyArray = new String[1];
        emptyArray[0] = "";
        return emptyArray;
    }

    String allArgs = command.substring(separatorIndex + 1);

    if (allArgs.length() == 0) {
        String *emptyArray = new String[1];
        emptyArray[0] = "";
        return emptyArray;
    }

    int count = 1;
    for (int i = 0; i < allArgs.length(); i++) {
        if (allArgs[i] == ',') {
            count++;
        }
    }

    String *argsArray = new String[count];

    int start = 0;
    int arrayIndex = 0;

    for (int i = 0; i <= allArgs.length(); i++) {
        if (i == allArgs.length() || allArgs[i] == ',') {
            argsArray[arrayIndex++] = allArgs.substring(start, i);
            start = i + 1;
        }
    }

    return argsArray;
}