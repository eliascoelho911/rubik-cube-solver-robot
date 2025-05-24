#include "HC05.h"

HC05::HC05(int rx, int tx, int state, int en, long baud) {
    rxPin = rx;
    txPin = tx;
    statePin = state;
    enPin = en;
    baudRate = baud;
    btSerial = new SoftwareSerial(rxPin, txPin);
    buffer[0] = '\0';
    bufferIndex = 0;
}

HC05::HC05(int rx, int tx, long baud) {
    rxPin = rx;
    txPin = tx;
    statePin = -1;
    enPin = -1;
    baudRate = baud;
    btSerial = new SoftwareSerial(rxPin, txPin);
    buffer[0] = '\0';
    bufferIndex = 0;
}

HC05::~HC05() { delete btSerial; }

void HC05::begin() {
    btSerial->begin(baudRate);
    delay(500);
}

size_t HC05::sendData(const char *data) { return btSerial->print(data); }

size_t HC05::sendData(uint8_t *buffer, size_t size) {
    return btSerial->write(buffer, size);
}

int HC05::available() { return btSerial->available(); }

int HC05::read() { return btSerial->read(); }

int HC05::readLine(char *buffer, size_t maxLength, char endMarker) {
    unsigned long startTime = millis();
    bool lineComplete = false;
    size_t charCount = 0;

    // Limite máximo de tempo de 1 segundo ou até receber o marcador final
    while ((millis() - startTime < 2000) && !lineComplete &&
           (charCount < maxLength - 1)) {
        if (btSerial->available() > 0) {
            char inChar = (char)btSerial->read();
            buffer[charCount++] = inChar;

            // Verifica se é o final da mensagem
            if (inChar == endMarker) {
                lineComplete = true;
            }
        } else {
            delay(10);
        }
    }

    // Garante que a string seja terminada corretamente
    buffer[charCount] = '\0';
    return charCount;
}

size_t HC05::readBytes(uint8_t *buffer, size_t length) {
    size_t count = 0;
    unsigned long startTime = millis();

    while (count < length && (millis() - startTime < 1000)) {
        if (btSerial->available()) {
            buffer[count] = btSerial->read();
            count++;
        }
    }

    return count;
}

void HC05::flush() {
    btSerial->flush();

    // Limpa quaisquer bytes pendentes no buffer
    while (btSerial->available()) {
        btSerial->read();
    }

    // Limpa o buffer interno
    buffer[0] = '\0';
    bufferIndex = 0;
}

SoftwareSerial *HC05::getSerial() { return btSerial; }