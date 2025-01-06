#include "cube.h"
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Cube cube = Cube();

void setup() {
    Serial.begin(9600);
    Serial.println("Iniciando o robô resolutor de cubo mágico...");

    cube.setup(5, 4, 1, 0);

    delay(10);

    cube.idle();

    // Exibe memória restante
    Serial.print("Memória restante: ");
    Serial.println(freeMemory());
}

void loop() {}

void runTest() {
    Serial.println("Iniciando teste...");

    cube.moveLeftGripper(true);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveLeftGripper(false);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveRightGripper(true);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveRightGripper(false);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveLeftHand(RIGHT);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveLeftHand(LEFT);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveLeftHand(MIDDLE);

    cube.moveRightHand(RIGHT);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    cube.moveRightHand(LEFT);
    if (!askSuccess()) {
        Serial.println("Teste falhou.");
        cube.idle();
        return;
    }

    Serial.println("Teste concluído com sucesso.");
    cube.idle();
}

bool askSuccess() {
    Serial.println("O movimento foi bem sucedido? (s/n)");
    while (true) {
        if (Serial.available() > 0) {
            char response = Serial.read();
            if (response == 's') {
                return true;
            } else if (response == 'n') {
                return false;
            }
        }
    }
}

int freeMemory() {
    extern int __heap_start, *__brkval;
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}
