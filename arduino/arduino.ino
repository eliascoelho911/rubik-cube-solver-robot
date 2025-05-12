#include "Arduino.h"
#include "HC05.h"
#include "commands.h"
#include "robot.h"
#include "serial.h"
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Robot robot = Robot(pwm);
HC05 bt(2, 3, 38400);

bool isConnected = false;
bool isReceiving = false;

// Buffer para receber comandos
char cmdBuffer[BT_BUFFER_SIZE];
CommandParser parser;

void setup() {
    Serial.begin(9600);
    Serial.println(F("Iniciando sistema..."));

    robot.begin();
    Serial.println(F("Robô inicializado"));

    bt.begin();

    Serial.println(F("Bluetooth inicializado"));
    Serial.println(F("Aguardando conexão Bluetooth..."));

    delay(10);
}

void loop() {
    if (bt.available()) {
        isConnected = true;

        // Lê comando para o buffer de caracteres
        int bytesRead = bt.readLine(cmdBuffer, BT_BUFFER_SIZE, '\n');

        if (bytesRead <= 0) {
            return;
        }

        // Converte para minúsculas
        for (int i = 0; i < bytesRead; i++) {
            if (cmdBuffer[i] >= 'A' && cmdBuffer[i] <= 'Z') {
                cmdBuffer[i] = cmdBuffer[i] - 'A' + 'a';
            }
        }

        Serial.print(F("Comando recebido: "));
        Serial.println(cmdBuffer);

        // Processa comandos separados por ponto e vírgula
        char *currentCommand = cmdBuffer;
        char *nextCommand = nullptr;

        do {
            // Encontra o próximo comando
            nextCommand = strchr(currentCommand, ';');
            if (nextCommand != nullptr) {
                *nextCommand =
                    '\0'; // Substitui o delimitador por terminação de string
                nextCommand++; // Move para o próximo caractere após o
                               // delimitador
            }

            // Processa o comando atual
            processCommand(currentCommand);

            // Avança para o próximo comando
            currentCommand = nextCommand;

        } while (currentCommand != nullptr && *currentCommand != '\0');

        Serial.println(F("Comando processado com sucesso"));
        bt.flush();
        Serial.flush();
    } else {
        if (isConnected) {
            Serial.println(F("Aguardando comando Bluetooth..."));
        }
        isConnected = false;
    }

    delay(200);
}

void processCommand(char *cmdStr) {
    // Inicializa o parser
    parser.reset();

    Serial.print(F("Processando comando: "));
    Serial.println(cmdStr);

    // Separa o comando em ID e argumentos
    char *separator = strchr(cmdStr, ':');
    if (separator == nullptr) {
        Serial.println(F("Formato de comando inválido"));
        return;
    }

    // Substitui o separador por terminação de string
    *separator = '\0';
    char *eventId = cmdStr;
    char *argsStr = separator + 1;

    // Obtém o tipo de comando
    CommandType cmdType = getCommandTypeFromString(eventId);
    if (cmdType == CMD_UNKNOWN) {
        Serial.print(F("Comando desconhecido: "));
        Serial.println(eventId);
        return;
    }

    // Cria a estrutura de comando
    Command cmd;
    cmd.type = cmdType;

    // Processa argumentos dependendo do tipo de comando
    if (cmdType == CMD_MOVE) {
        // Processa os parâmetros (motor e movimento)
        // Formato: move:motor,direção
        char *args[2] = {nullptr, nullptr};
        parseArgs(argsStr, args, 2);

        if (args[0] == nullptr || args[1] == nullptr) {
            Serial.println(F("Argumentos insuficientes para comando move"));
            return;
        }

        // Obtém o tipo de motor
        MotorType motorType = getMotorTypeFromString(args[0]);
        if (motorType == MOTOR_UNKNOWN) {
            Serial.print(F("Motor desconhecido: "));
            Serial.println(args[0]);
            return;
        }

        cmd.params.moveCmd.motor = motorType;

        // Processa movimento dependendo do tipo de motor
        if (motorType == MOTOR_LEFT_HAND || motorType == MOTOR_RIGHT_HAND) {
            HandDirection dir = getHandDirectionFromString(args[1]);
            if (dir == HAND_DIR_UNKNOWN) {
                Serial.print(F("Direção desconhecida: "));
                Serial.println(args[1]);
                return;
            }
            cmd.params.moveCmd.handDir = dir;
        } else if (motorType == MOTOR_LEFT_GRIPPER ||
                   motorType == MOTOR_RIGHT_GRIPPER) {
            GripperAction action = getGripperActionFromString(args[1]);
            if (action == GRIPPER_UNKNOWN) {
                Serial.print(F("Ação de garra desconhecida: "));
                Serial.println(args[1]);
                return;
            }
            cmd.params.moveCmd.gripperAction = action;
        }
    }

    // Executa o comando
    robot.exec(cmd);
    Serial.println(F("Comando executado com sucesso"));
}

// Função para dividir uma string em argumentos separados por vírgula
void parseArgs(char *argsStr, char **argsArray, uint8_t maxArgs) {
    uint8_t argCount = 0;

    // Se a string está vazia, retorna sem argumentos
    if (argsStr == nullptr || *argsStr == '\0') {
        return;
    }

    // O primeiro argumento começa no início da string
    argsArray[argCount++] = argsStr;

    // Procura por vírgulas e substitui por terminadores de string
    while (argCount < maxArgs) {
        char *comma = strchr(argsStr, ',');
        if (comma == nullptr) {
            break;
        }

        // Substitui a vírgula por terminador e avança o ponteiro
        *comma = '\0';
        argsStr = comma + 1;

        // Armazena o ponteiro para o próximo argumento
        argsArray[argCount++] = argsStr;
    }
}