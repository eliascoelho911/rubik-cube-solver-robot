#include "Arduino.h"
#include "HC05.h"
#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot robot = Robot(pwm);
HC05 bt(2, 3, 38400);

bool isConnected = false;
bool isReceiving = false;

void setup() {
    Serial.begin(9600);
    Serial.println("Iniciando sistema...");

    robot.begin();
    Serial.println("Robô inicializado");

    bt.begin();

    Serial.println("Bluetooth inicializado");
    Serial.println("Aguardando conexão Bluetooth...");

    delay(10);
}

void loop() {
    if (bt.available()) {
        isConnected = true;

        String command = bt.readString('\n');
        command.trim();
        command.toLowerCase();

        Serial.println("Comando recebido: " + command);

        if (command.length() == 0) {
            return;
        }

        do {
            int endCommandIndex = command.indexOf(';');
            String currentCommand = command.substring(0, endCommandIndex);
            Serial.println("Comando atual: " + currentCommand);

            int separatorIndex = currentCommand.indexOf(':');
            Serial.println("Índice do separador: " + String(separatorIndex));

            String eventId = getEventId(currentCommand, separatorIndex);
            Serial.println("ID do evento: " + eventId);

            String *args = getArgs(currentCommand, separatorIndex);
            Serial.println("Argumentos(" + String(sizeof(args)) + ": ");
            for (int i = 0; i < sizeof(args); i++) {
                Serial.println("Arg[" + String(i) + "]: " + args[i]);
            }
            Serial.println(")");
            robot.exec(eventId, args);
            Serial.println("Comando executado com sucesso");

            if (args != nullptr) {
                delete[] args;
            }

            if (endCommandIndex >= command.length() - 1) {
                break;
            }

            command = command.substring(endCommandIndex + 1);
            command.trim();

            Serial.println("Comando restante(" + String(command.length()) +
                           "): " + command);
        } while (command.length() > 0);

        Serial.println("Comando processado com sucesso");
        bt.flush();
        Serial.flush();
    } else {
        if (isConnected) {
            Serial.println("Aguardando comando Bluetooth...");
        }
        isConnected = false;
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
    Serial.println("Iniciando getArgs");
    Serial.println("Comando: " + command);
    Serial.println("Índice do separador: " + String(separatorIndex));
    if (separatorIndex < 0 || separatorIndex >= command.length() - 1) {
        String *emptyArray = new String[1];
        emptyArray[0] = "";
        return emptyArray;
    }

    String allArgs = command.substring(separatorIndex + 1);
    allArgs.trim();
    Serial.println("Todos os argumentos: " + String(allArgs.length()));

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

    Serial.println("Número de argumentos: " + String(count));

    String *argsArray = new String[count];

    int start = 0;
    int arrayIndex = 0;

    for (int i = 0; i <= allArgs.length(); i++) {
        if (i == allArgs.length() || allArgs[i] == ',') {
            String arg = allArgs.substring(start, i);
            arg.trim();
            argsArray[arrayIndex++] = arg;
            Serial.println("Arg[" + String(arrayIndex - 1) + "]: " + arg);
            start = i + 1;
        }
    }

    return argsArray;
}