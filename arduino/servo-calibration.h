#ifndef SERVO_CALIBRATION_H
#define SERVO_CALIBRATION_H

#include "servo.h"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

// Constantes para o controle do servo
extern const int servoMin;
extern const int servoMax;

// Funções públicas
void setupServoCalibration();
void loopServoCalibration();

// Função para processar dados do buffer serial
void processSerialBuffer();

// Função para verificar timeout serial
void checkSerialTimeout();

// Função para atualizar a posição do servo com base no sensor
void updateServoPosition();

#endif // SERVO_CALIBRATION_H