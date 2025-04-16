#include "test_mode.h"

TestMode::TestMode(Robot &robot) : _robot(robot) {}

void TestMode::run() {
    while (true) {
        showMenu();
        int option = readInt("Escolha uma opção: ");

        switch (option) {
        case 1:
            handleCubeMovement();
            break;
        case 2:
            handleGripperMovement();
            break;
        case 3:
            handleHandMovement();
            break;
        default:
            Serial.println("Opção inválida!");
            break;
        }
    }
}

void TestMode::showMenu() {
    Serial.println("\nMenu de Teste:");
    Serial.println("1. Movimentar o cubo");
    Serial.println("2. Movimentar a garra");
    Serial.println("3. Movimentar a mão");
}

void TestMode::handleCubeMovement() {
    while (true) {
        String move = readString("Digite o movimento (s para sair): ");
        if (move == "s" || move == "S")
            break;
        _robot.moveCube(move);
    }
}

void TestMode::handleGripperMovement() {
    while (true) {
        Serial.println("\nMenu da Garra:");
        Serial.println("1. Abrir garra esquerda");
        Serial.println("2. Fechar garra esquerda");
        Serial.println("3. Abrir garra direita");
        Serial.println("4. Fechar garra direita");
        Serial.println("s. Voltar ao menu principal");

        String option = readString("Escolha uma opção: ");

        if (option == "s" || option == "S")
            break;

        switch (option.toInt()) {
        case 1:
            _robot._lGripper.open();
            break;
        case 2:
            _robot._lGripper.close();
            break;
        case 3:
            _robot._rGripper.open();
            break;
        case 4:
            _robot._rGripper.close();
            break;
        default:
            Serial.println("Opção inválida!");
            break;
        }
    }
}

void TestMode::handleHandMovement() {
    while (true) {
        Serial.println("\nMenu da Mão:");
        Serial.println("1. Mão esquerda para meio");
        Serial.println("2. Mão esquerda para mínimo");
        Serial.println("3. Mão esquerda para máximo");
        Serial.println("4. Mão direita para meio");
        Serial.println("5. Mão direita para mínimo");
        Serial.println("6. Mão direita para máximo");
        Serial.println("s. Voltar ao menu principal");

        String option = readString("Escolha uma opção: ");

        if (option == "s" || option == "S")
            break;

        switch (option.toInt()) {
        case 1:
            _robot._lHand.move(0);
            break;
        case 2:
            _robot._lHand.move(-1);
            break;
        case 3:
            _robot._lHand.move(1);
            break;
        case 4:
            _robot._rHand.move(0);
            break;
        case 5:
            _robot._rHand.move(-1);
            break;
        case 6:
            _robot._rHand.move(1);
            break;
        default:
            Serial.println("Opção inválida!");
            break;
        }
    }
}