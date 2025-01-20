#include "serial.h"

int readInt(const char *question) {
    if (question != nullptr) {
        Serial.print(question);
    }

    while (Serial.available() == 0) {
        // Wait for input
    }

    return Serial.parseInt();
}

String readString(const char *question) {
    if (question != nullptr) {
        Serial.print(question);
    }

    while (Serial.available() == 0) {
        // Wait for input
    }

    return Serial.readString();
}

void awaitInput(const char *message) {
    if (message != nullptr) {
        Serial.print(message);
    }

    readInt();
}