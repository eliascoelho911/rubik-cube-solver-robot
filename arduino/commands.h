#ifndef COMMANDS_H
#define COMMANDS_H

// Enumeração para os tipos de eventos/comandos
typedef enum {
    CMD_MOVE = 0,    // move - motor
    CMD_RECEIVE = 1, // receive - receber cubo
    CMD_RELEASE = 2, // release - soltar cubo
    CMD_UNKNOWN = 255
} CommandType;

// Enumeração para os tipos de motores
typedef enum {
    MOTOR_LEFT_HAND = 0,     // hl - mão esquerda
    MOTOR_RIGHT_HAND = 1,    // hr - mão direita
    MOTOR_LEFT_GRIPPER = 2,  // gl - garra esquerda
    MOTOR_RIGHT_GRIPPER = 3, // gr - garra direita
    MOTOR_UNKNOWN = 255
} MotorType;

// Enumeração para as direções das mãos
typedef enum {
    HAND_DIR_CW = 0,  // cw - sentido horário
    HAND_DIR_CCW = 1, // cw' - sentido anti-horário
    HAND_DIR_MID = 2, // mid - posição central
    HAND_DIR_UNKNOWN = 255
} HandDirection;

// Enumeração para as ações das garras
typedef enum {
    GRIPPER_OPEN = 0,  // open - abrir
    GRIPPER_CLOSE = 1, // close - fechar
    GRIPPER_UNKNOWN = 255
} GripperAction;

#include <avr/pgmspace.h>

// Tabelas para converter entre string e enum
// Estas tabelas são armazenadas na memória flash para economizar RAM
const char CMD_MOVE_STR[] PROGMEM = "move";
const char CMD_RECEIVE_STR[] PROGMEM = "receive";
const char CMD_RELEASE_STR[] PROGMEM = "release";

const char MOTOR_LEFT_HAND_STR[] PROGMEM = "hl";
const char MOTOR_RIGHT_HAND_STR[] PROGMEM = "hr";
const char MOTOR_LEFT_GRIPPER_STR[] PROGMEM = "gl";
const char MOTOR_RIGHT_GRIPPER_STR[] PROGMEM = "gr";

const char HAND_DIR_CW_STR[] PROGMEM = "cw";
const char HAND_DIR_CCW_STR[] PROGMEM = "cw'";
const char HAND_DIR_MID_STR[] PROGMEM = "mid";

const char GRIPPER_OPEN_STR[] PROGMEM = "open";
const char GRIPPER_CLOSE_STR[] PROGMEM = "close";

// Estrutura para comando completo
struct Command {
    CommandType type;
    union {
        struct {
            MotorType motor;
            union {
                HandDirection handDir;
                GripperAction gripperAction;
            };
        } moveCmd;
    } params;
};

// Funções de conversão entre string e enum
CommandType getCommandTypeFromString(const char *cmdStr);
MotorType getMotorTypeFromString(const char *motorStr);
HandDirection getHandDirectionFromString(const char *dirStr);
GripperAction getGripperActionFromString(const char *actionStr);

// Funções para obter string a partir de enum (para mensagens de log)
const char *getCommandTypeString(CommandType cmd);
const char *getMotorTypeString(MotorType motor);
const char *getHandDirectionString(HandDirection dir);
const char *getGripperActionString(GripperAction action);

// Estrutura para decodificação de comandos da forma cmd:param1,param2
#define MAX_CMD_LEN 16
#define MAX_ARGS 2

struct CommandParser {
    char cmdBuffer[MAX_CMD_LEN];
    char args[MAX_ARGS][MAX_CMD_LEN];
    uint8_t numArgs;

    // Inicializa o parser
    void reset() {
        cmdBuffer[0] = '\0';
        args[0][0] = '\0';
        args[1][0] = '\0';
        numArgs = 0;
    }
};

#endif // COMMANDS_H