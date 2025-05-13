#include "commands.h"
#include <Arduino.h>

// Função para comparar uma string na memória flash com uma string na RAM
bool compareProgmemString(const char *progmemStr, const char *ramStr) {
    char c;
    size_t i = 0;

    while ((c = pgm_read_byte(progmemStr + i)) != 0) {
        if (c != ramStr[i])
            return false;
        i++;
    }

    return ramStr[i] == 0; // Verifica se a string RAM também terminou
}

// Implementação das funções de conversão
CommandType getCommandTypeFromString(const char *cmdStr) {
    if (compareProgmemString(CMD_MOVE_STR, cmdStr))
        return CMD_MOVE;
    if (compareProgmemString(CMD_RECEIVE_STR, cmdStr))
        return CMD_RECEIVE;
    if (compareProgmemString(CMD_RELEASE_STR, cmdStr))
        return CMD_RELEASE;
    return CMD_UNKNOWN;
}

MotorType getMotorTypeFromString(const char *motorStr) {
    if (compareProgmemString(MOTOR_LEFT_HAND_STR, motorStr))
        return MOTOR_LEFT_HAND;
    if (compareProgmemString(MOTOR_RIGHT_HAND_STR, motorStr))
        return MOTOR_RIGHT_HAND;
    if (compareProgmemString(MOTOR_LEFT_GRIPPER_STR, motorStr))
        return MOTOR_LEFT_GRIPPER;
    if (compareProgmemString(MOTOR_RIGHT_GRIPPER_STR, motorStr))
        return MOTOR_RIGHT_GRIPPER;
    return MOTOR_UNKNOWN;
}

HandDirection getHandDirectionFromString(const char *dirStr) {
    if (compareProgmemString(HAND_DIR_CW_STR, dirStr))
        return HAND_DIR_CW;
    if (compareProgmemString(HAND_DIR_CCW_STR, dirStr))
        return HAND_DIR_CCW;
    if (compareProgmemString(HAND_DIR_MID_STR, dirStr))
        return HAND_DIR_MID;
    return HAND_DIR_UNKNOWN;
}

GripperAction getGripperActionFromString(const char *actionStr) {
    if (compareProgmemString(GRIPPER_OPEN_STR, actionStr))
        return GRIPPER_OPEN;
    if (compareProgmemString(GRIPPER_CLOSE_STR, actionStr))
        return GRIPPER_CLOSE;
    return GRIPPER_UNKNOWN;
}

// Implementação das funções para obter strings a partir de enums
const char *getCommandTypeString(CommandType cmd) {
    switch (cmd) {
    case CMD_MOVE:
        return CMD_MOVE_STR;
    case CMD_RECEIVE:
        return CMD_RECEIVE_STR;
    case CMD_RELEASE:
        return CMD_RELEASE_STR;
    default:
        return "unknown";
    }
}

const char *getMotorTypeString(MotorType motor) {
    switch (motor) {
    case MOTOR_LEFT_HAND:
        return MOTOR_LEFT_HAND_STR;
    case MOTOR_RIGHT_HAND:
        return MOTOR_RIGHT_HAND_STR;
    case MOTOR_LEFT_GRIPPER:
        return MOTOR_LEFT_GRIPPER_STR;
    case MOTOR_RIGHT_GRIPPER:
        return MOTOR_RIGHT_GRIPPER_STR;
    default:
        return "unknown";
    }
}

const char *getHandDirectionString(HandDirection dir) {
    switch (dir) {
    case HAND_DIR_CW:
        return HAND_DIR_CW_STR;
    case HAND_DIR_CCW:
        return HAND_DIR_CCW_STR;
    case HAND_DIR_MID:
        return HAND_DIR_MID_STR;
    default:
        return "unknown";
    }
}

const char *getGripperActionString(GripperAction action) {
    switch (action) {
    case GRIPPER_OPEN:
        return GRIPPER_OPEN_STR;
    case GRIPPER_CLOSE:
        return GRIPPER_CLOSE_STR;
    default:
        return "unknown";
    }
}