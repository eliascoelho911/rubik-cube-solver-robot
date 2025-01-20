#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

int readInt(const char *question = nullptr) {
    if (question != nullptr) {
        Serial.print(*question);
    }

    while (Serial.available() == 0) {
        // Wait for input
    }

    return Serial.read();
}

String readString(const char *question = nullptr) {
    if (question != nullptr) {
        Serial.print(*question);
    }

    while (Serial.available() == 0) {
        // Wait for input
    }

    return Serial.readString();
}

void awaitInput(const char *message = nullptr) {
    if (message != nullptr) {
        Serial.print(*message);
    }

    readInt();
}

#endif