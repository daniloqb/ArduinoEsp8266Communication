#include <SoftwareSerial.h>

#define  BAUNDRATE 9600

const byte RX_PIN = 6;
const byte TX_PIN = 7;
const int MAX_BUFFER = 200;

char buff[MAX_BUFFER];

int val = 0;
SoftwareSerial my_serial(RX_PIN, TX_PIN); 

void setup() {
    Serial.begin(BAUNDRATE);
    my_serial.begin(BAUNDRATE);
    Serial.println("Initializing");
}

void loop() {  
  int index = 0;
  char c;


/*
 * PARTE 01 -- RECEBENDO DADOS DA SOFTSERIAL
 */

  if (my_serial.available() > 0) {

    for (int i = 0; i < MAX_BUFFER; i++) {
       buff[i] = '\0';
    }

    while (my_serial.available()) {
      c = my_serial.read();

 
      delay(1);
      if ((c != '\r' && c != '\n') && index < MAX_BUFFER) {
         buff[index++] = c;
      }


    }

    Serial.println(buff);
  }


/*
 *  PARTE 02 -- EXECUTANDO OPERACOES
 */

 val = analogRead(A0);

 /*
  * PARTE 03 -- ENVIANDO DADOS PARA A SOFTWARESERIAL
  */


  my_serial.println(val);
  Serial.print("Sending:");
  Serial.println(val);  

  /*
   *  PART04 -- DELAY DE EXECUCAO
   */

  delay(3000);
   
}
