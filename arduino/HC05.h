#ifndef HC05_h
#define HC05_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class HC05 {
  private:
    SoftwareSerial *btSerial;
    int rxPin;
    int txPin;
    int statePin;
    int enPin;
    long baudRate;
    String buffer;

  public:
    /**
     * Construtor da classe HC05
     *
     * @param rx Pino RX (conecta ao TX do HC-05)
     * @param tx Pino TX (conecta ao RX do HC-05)
     * @param state Pino STATE do HC-05 (opcional, -1 se não utilizado)
     * @param en Pino EN do HC-05 (opcional para modo AT, -1 se não utilizado)
     * @param baud Taxa de transmissão (padrão: 9600)
     */
    HC05(int rx, int tx, int state = -1, int en = -1, long baud = 9600);

    /**
     * Construtor da classe HC05 sem pinos de estado e habilitação
     *
     * @param rx Pino RX (conecta ao TX do HC-05)
     * @param tx Pino TX (conecta ao RX do HC-05)
     * @param baud Taxa de transmissão (padrão: 9600)
     */
    HC05(int rx, int tx, long baud = 9600);

    /**
     * Destrutor da classe HC05
     */
    ~HC05();

    void begin();

    /**
     * Enviar dados pela conexão Bluetooth
     *
     * @param data String de dados a serem enviados
     * @return Número de bytes enviados
     */
    size_t sendData(String data);

    /**
     * Enviar dados em formato binário pela conexão Bluetooth
     *
     * @param buffer Array de bytes a serem enviados
     * @param size Tamanho do array
     * @return Número de bytes enviados
     */
    size_t sendData(uint8_t *buffer, size_t size);

    /**
     * Verifica se há dados disponíveis para leitura
     *
     * @return Número de bytes disponíveis
     */
    int available();

    /**
     * Lê um byte da conexão Bluetooth
     *
     * @return Byte lido ou -1 se nenhum dado disponível
     */
    int read();

    /**
     * Lê dados disponíveis como uma string
     *
     * @param endMarker Caractere que marca o fim da mensagem (padrão: '\n')
     * @return String com os dados lidos ou string vazia se nada disponível
     */
    String readString(char endMarker = '\n');

    /**
     * Lê dados para um buffer
     *
     * @param buffer Array onde os dados serão armazenados
     * @param length Tamanho máximo a ser lido
     * @return Número de bytes lidos
     */
    size_t readBytes(uint8_t *buffer, size_t length);

    /**
     * Limpa o buffer de recepção
     */
    void flush();

    /**
     * Método para acessar diretamente o objeto SoftwareSerial
     *
     * @return Ponteiro para o objeto SoftwareSerial
     */
    SoftwareSerial *getSerial();
};

#endif