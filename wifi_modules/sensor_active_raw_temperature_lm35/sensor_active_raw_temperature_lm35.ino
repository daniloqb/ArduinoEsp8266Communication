/* 2018-04-25
 * Danilo Queiroz Barbosa
 * daniloqb@electronicdrops.com
 * electronicdrops.com member
 * 
 * This sketch is a example of sending raw temperature data over wifi using arduino-esp8266-lm35
 */




#define DEBUG 1
#define USE_SOFTWARE_SERIAL 0
#define  BAUNDRATE 9600
#define UPDATE_TIME 3000


#if USE_SOFTWARE_SERIAL == 1

  #include <SoftwareSerial.h>
  const byte RX_PIN = 6;
  const byte TX_PIN = 7;
  SoftwareSerial my_serial(RX_PIN, TX_PIN); 
  #define SERIAL my_serial

#elif USE_SOFTWARE_SERIAL == 0

  #define SERIAL Serial
  #define DEBUG  0

#endif

const int MAX_BUFFER = 200;
char buff[MAX_BUFFER];


/*
 * DECLARING SENSOR OBJECT
 */

 #include "TemperatureSensors.h"
 
TemperatureSensorLM35 sensor = TemperatureSensorLM35(A0);


void setup() {

  SERIAL.begin(BAUNDRATE);

  #if DEBUG == 1  
    Serial.begin(BAUNDRATE);
    Serial.println("Initializing");
  #endif

  sensor.begin(); //initializing sensor
  
}

void loop() {  
  int index = 0;
  char c;


/*
 * PART 01 -- RECEIVING DATA FROM SERIAL
 */

  if (SERIAL.available() > 0) {

    for (int i = 0; i < MAX_BUFFER; i++) {
       buff[i] = '\0';
    }

    while (SERIAL.available()) {
      c = SERIAL.read();

 
      delay(1);
      if ((c != '\r' && c != '\n') && index < MAX_BUFFER) {
         buff[index++] = c;
      }


    }

    #if DEBUG == 1
      Serial.println(buff);
    #endif
  }

  


/*
 *  PART 02 -- GETTING DATA FROM SENSOR
 *  
 */

 sensor.update(); // update the values

 float temperature = sensor.getTemperature();
 

 /*
  * PARTE 03 -- ENVIANDO DADOS PARA A SOFTWARESERIAL
  */


  SERIAL.println(temperature);

  #if DEBUG == 1
    Serial.print("Sending:");
    Serial.println(temperature);  
  #endif
  /*
   *  PART04 -- DELAY DE EXECUCAO
   */

  delay(UPDATE_TIME);
   
}
