
#define  BAUNDRATE 9600

const int MAX_BUFFER = 200;

const int INTERVAL = 3000;

char buff[MAX_BUFFER];

int val = 0;


void setup() {
    Serial.begin(BAUNDRATE);

}

void loop() {  
  int index = 0;
  char c;


/*
 * PARTE 01 -- RECEBENDO DADOS DA SERIAL
 */

  if (Serial.available() > 0) {

    for (int i = 0; i < MAX_BUFFER; i++) {
       buff[i] = '\0';
    }

    while (Serial.available()) {
      c = Serial.read();

 
      delay(1);
      if ((c != '\r' && c != '\n') && index < MAX_BUFFER) {
         buff[index++] = c;
      }


    }

  }


/*
 *  PARTE 02 -- EXECUTANDO OPERACOES
 */

 val = analogRead(A0);

 /*
  * PARTE 03 -- ENVIANDO DADOS PARA A SERIAL
  */


  Serial.println(val);
 

  /*
   *  PART04 -- DELAY DE EXECUCAO
   */

  delay(INTERVAL);
   
}
