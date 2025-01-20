#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

int readInt(const char *question = nullptr);

String readString(const char *question = nullptr);

void awaitInput(const char *message = nullptr);

#endif