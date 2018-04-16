/* 2018-04-12
 * Danilo Queiroz Barbosa
 * electronicdrops.com member
 * 
 * This sketch is a simple example how to send data over a period of time throught serial
 * Was designed to be used together a ESP8266. The data is send to esp82 throught serial
 * and ESP8266 relay the data to a server.
 * 
 * This first part send a HTTP POST/GET data.
 */
#include <TimedTask.h>



#define DEBUG 1
#define USE_SOFTWARE_SERIAL 1
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

const int MAX_BUFFER = 500;

char buff[MAX_BUFFER];



void senddata(){

SERIAL.println("user=arduino&password=123456");
  
}

TimedTask t = TimedTask(senddata,3000);



void setup() {

  SERIAL.begin(BAUNDRATE);

  #if DEBUG == 1  
    Serial.begin(BAUNDRATE);
    Serial.println("Initializing");
  #endif
}

void loop() {

  t.run();

    char c;
    int index = 0;
 
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


   
}
