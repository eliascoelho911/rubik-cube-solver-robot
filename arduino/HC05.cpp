#include "HC05.h"

HC05::HC05(int rx, int tx, int state, int en, long baud) {
    rxPin = rx;
    txPin = tx;
    statePin = state;
    enPin = en;
    baudRate = baud;
    btSerial = new SoftwareSerial(rxPin, txPin);
    buffer = "";
}

HC05::HC05(int rx, int tx, long baud) {
    rxPin = rx;
    txPin = tx;
    statePin = -1;
    enPin = -1;
    baudRate = baud;
    btSerial = new SoftwareSerial(rxPin, txPin);
    buffer = "";
}

HC05::~HC05() { delete btSerial; }

bool HC05::begin() {
    btSerial->begin(baudRate);

    if (statePin != -1) {
        pinMode(statePin, INPUT);
    }

    if (enPin != -1) {
        pinMode(enPin, OUTPUT);
        digitalWrite(enPin, LOW);
    }

    delay(500);

    if (enterATMode()) {
        btSerial->println("AT");
        delay(100);

        unsigned long startTime = millis();
        buffer = "";

        while (millis() - startTime < 1000) {
            if (btSerial->available()) {
                char c = btSerial->read();
                buffer += c;

                if (buffer.indexOf("OK") != -1) {
                    exitATMode();
                    return true;
                }
            }
        }

        exitATMode();
    }

    return false;
}

bool HC05::enterATMode() {
    if (enPin == -1) {
        return false;
    }

    digitalWrite(enPin, HIGH);
    delay(100);
    btSerial->begin(38400);
    delay(100);

    return true;
}

void HC05::exitATMode() {
    if (enPin != -1) {
        btSerial->end();
        delay(100);
        digitalWrite(enPin, LOW);
        delay(100);
        btSerial->begin(baudRate);
        delay(100);
    }
}

bool HC05::isConnected() {
    if (statePin != -1) {
        return digitalRead(statePin) == HIGH;
    } else {
        return true;
    }
}

bool HC05::configureAsSlave(String name, String pin) {
    if (!enterATMode()) {
        return false;
    }

    bool success = true;

    // Restaura configurações de fábrica
    btSerial->println("AT+ORGL");
    delay(100);

    // Configura como escravo
    btSerial->println("AT+ROLE=0");
    delay(100);

    // Configura o nome do dispositivo
    btSerial->print("AT+NAME=");
    btSerial->println(name);
    delay(100);

    // Configura PIN
    btSerial->print("AT+PSWD=");
    btSerial->println(pin);
    delay(100);

    // Configura modo escravo (aguardando conexão)
    btSerial->println("AT+CMODE=0");
    delay(100);

    // Configura taxa de transmissão após sair do modo AT
    btSerial->print("AT+UART=");
    btSerial->print(baudRate);
    btSerial->println(",0,0");
    delay(100);

    // Valida configurações
    // Implementação básica - poderia ser expandida para validar cada comando

    exitATMode();
    return success;
}

size_t HC05::sendData(String data) { return btSerial->print(data); }

size_t HC05::sendData(uint8_t *buffer, size_t size) {
    return btSerial->write(buffer, size);
}

int HC05::available() { return btSerial->available(); }

int HC05::read() { return btSerial->read(); }

String HC05::readString(char endMarker) {
    String receivedString = "";
    unsigned long startTime = millis();
    bool stringComplete = false;

    // Timeout de 1 segundo ou até receber o marcador de final
    while (millis() - startTime < 1000 && !stringComplete) {
        if (btSerial->available() > 0) {
            char inChar = (char)btSerial->read();
            receivedString += inChar;

            // Verifica se é o final da mensagem
            if (inChar == endMarker) {
                stringComplete = true;
            }
        }
    }

    return receivedString;
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
}

SoftwareSerial *HC05::getSerial() { return btSerial; }