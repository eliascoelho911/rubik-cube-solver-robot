#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>
#include <stdarg.h>

class Logger {
  private:
    static Logger *instance;
    Logger() {}

    // Buffer para formatação de mensagens
    char _messageBuffer[128];

    // Método interno para formatar strings
    void _formatMessage(const char *format, va_list args) {
        vsnprintf(_messageBuffer, sizeof(_messageBuffer), format, args);
    }

  public:
    static Logger *getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return instance;
    }

    void info(const char *format, ...) {
        va_list args;
        va_start(args, format);
        _formatMessage(format, args);
        va_end(args);

        Serial.print("[INFO] ");
        Serial.println(_messageBuffer);
    }

    void error(const char *format, ...) {
        va_list args;
        va_start(args, format);
        _formatMessage(format, args);
        va_end(args);

        Serial.print("[ERROR] ");
        Serial.println(_messageBuffer);
    }

    void debug(const char *format, ...) {
        va_list args;
        va_start(args, format);
        _formatMessage(format, args);
        va_end(args);

        Serial.print("[DEBUG] ");
        Serial.println(_messageBuffer);
    }
};

#endif // LOGGER_H