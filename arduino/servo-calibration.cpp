#include "servo-calibration.h"

// Crie uma instância do driver PWM
Adafruit_PWMServoDriver servoPmm = Adafruit_PWMServoDriver();

// Inicializa com valores padrão
int servoPin = 0; // Pino padrão inicial
const int servoMin = 120;
const int servoMax = 510;
int lastPulseValue = 0;

// Ponteiro para o objeto servo - permitirá recriar o objeto quando necessário
RobotServo *servo = nullptr;

// Buffer para armazenar dados recebidos
char serialBuffer[10];
int bufferIndex = 0;
unsigned long lastSerialData = 0;
const unsigned long serialTimeout = 100; // Timeout em ms

void setupServoCalibration() {
    // Inicialize o driver PWM com a frequência padrão de 50Hz
    servoPmm.begin();
    servoPmm.setOscillatorFrequency(27000000);
    servoPmm.setPWMFreq(50);

    // Cria o servo inicialmente
    servo = new RobotServo(servoPmm, servoPin, servoMin, servoMax);

    // Inicialize a comunicação serial
    Serial.begin(9600);
    Serial.println("Sistema de controle de servo iniciado");
    Serial.println("Envie o número do pino (0-15)");

    pinMode(A0, INPUT);
    pinMode(7, OUTPUT);
    digitalWrite(7, HIGH);
}

void loopServoCalibration() {
    // Verifica se há dados disponíveis no Serial sem bloquear
    while (Serial.available() > 0) {
        char c = Serial.read();
        lastSerialData = millis();

        // Se receber um caractere de nova linha ou retorno, processa o buffer
        if (c == '\n' || c == '\r') {
            if (bufferIndex > 0) {
                processSerialBuffer();
            }
        }
        // Se não for um caractere de controle, adiciona ao buffer
        else if (bufferIndex < sizeof(serialBuffer) - 1) {
            serialBuffer[bufferIndex++] = c;
        }
    }

    // Verifica timeout para limpar o buffer se receber dados parciais
    checkSerialTimeout();

    // Atualiza a posição do servo com base no sensor
    updateServoPosition();

    // Pequeno atraso para estabilidade
    delay(20);
}

void processSerialBuffer() {
    serialBuffer[bufferIndex] = '\0'; // Finaliza a string

    // Converte para inteiro
    int newPin = atoi(serialBuffer);

    // Verifica se é um pino válido (0-15 para o Adafruit PWM Shield)
    if (newPin >= 0 && newPin <= 15) {
        // Atualiza o pino do servo
        servoPin = newPin;

        // Deleta o servo existente e cria uma nova instância
        if (servo != nullptr) {
            delete servo;
        }
        servo = new RobotServo(servoPmm, servoPin, servoMin, servoMax);

        Serial.print("Pino do servo alterado para: ");
        Serial.println(servoPin);
    } else {
        Serial.println("Pino inválido. Use valores entre 0 e 15.");
    }

    // Limpa o buffer
    bufferIndex = 0;
}

void checkSerialTimeout() {
    if (bufferIndex > 0 && millis() - lastSerialData > serialTimeout) {
        Serial.println("Timeout na entrada serial");
        bufferIndex = 0;
    }
}

void updateServoPosition() {
    if (servo != nullptr) {
        int sensorValue = analogRead(A0);
        int pulseValue = map(sensorValue, 0, 1023, servoMin, servoMax);
        if (pulseValue > lastPulseValue + 5 ||
            pulseValue < lastPulseValue - 5) {
            lastPulseValue = pulseValue;
            servo->write(pulseValue);
            Serial.print("Pulse Value: ");
            Serial.println(pulseValue);
        }
    }
}