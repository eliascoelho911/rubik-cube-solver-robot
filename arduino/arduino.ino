#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#define SERVO_FREQ 50

#define L_HAND_SERVO_IDLE_PULSE 300
#define L_HAND_SERVO_OFFSET_PULSE 180
#define L_HAND_SERVO_CHANNEL 0

#define R_HAND_SERVO_IDLE_PULSE 300
#define R_HAND_SERVO_OFFSET_PULSE 180
#define R_HAND_SERVO_CHANNEL 1

#define L_GRIPPER_SERVO_OPPENED_PULSE 395
#define L_GRIPPER_SERVO_CLOSED_PULSE 460
#define L_GRIPPER_SERVO_CHANNEL 2

#define R_GRIPPER_SERVO_OPPENED_PULSE 460
#define R_GRIPPER_SERVO_CLOSED_PULSE 395
#define R_GRIPPER_SERVO_CHANNEL 3

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando o robô resolutor de cubo mágico...");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

  delay(10);

  moveTest();
}

void loop() {}

void moveCube(String moveNotation) {
  if (moveNotation == "L") {
    pwm.setPWM(L_GRIPPER_SERVO_CHANNEL, 0, L_GRIPPER_SERVO_CLOSED_PULSE);
    delay(1000);
    moveServo(L_HAND_SERVO_CHANNEL, 1);
  } else if (moveNotation == "L'") {
    moveServo(L_HAND_SERVO_CHANNEL, -1);
  } else if (moveNotation == "R") {
    moveServo(R_HAND_SERVO_CHANNEL, 1);
  } else if (moveNotation == "R'") {
    moveServo(R_HAND_SERVO_CHANNEL, -1);
  } else {
    moveServo(L_HAND_SERVO_CHANNEL, 0);
    delay(1000);
    pwm.setPWM(R_GRIPPER_SERVO_CHANNEL, 0, R_GRIPPER_SERVO_OPPENED_PULSE);
    delay(1000);
    moveServo(R_HAND_SERVO_CHANNEL, 0);
  }
}

// Implementar trava de segurança para evitar colisões
void moveServo(int channel, int direction) {
  int pulse = calcPulse(channel, direction);
  pwm.setPWM(channel, 0, pulse);
  Serial.println("Movendo servo " + String(channel) + " para " +
                 String(direction) + " com o pulso " + String(pulse));
  delay(500);
}

int calcPulse(int channel, int direction) {
  int idlePulse;
  int offsetPulse;

  if (channel == L_HAND_SERVO_CHANNEL) {
    idlePulse = L_HAND_SERVO_IDLE_PULSE;
    offsetPulse = L_HAND_SERVO_OFFSET_PULSE;
  } else if (channel == R_HAND_SERVO_CHANNEL) {
    idlePulse = R_HAND_SERVO_IDLE_PULSE;
    offsetPulse = R_HAND_SERVO_OFFSET_PULSE;
  }

  int minPulse = idlePulse - offsetPulse;
  int maxPulse = idlePulse + offsetPulse;

  return map(direction, -1, 1, minPulse, maxPulse);
}

void moveTest() {
  while (true) {
    Serial.println("Digite o movimento: ");

    while (Serial.available() == 0) {
    }

    String moveNotation = Serial.readString();

    if (moveNotation == "exit") {
      return;
    }

    moveCube(moveNotation);
  }
}
