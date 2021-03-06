/* 2018-04-12
 * Danilo Queiroz Barbosa
 * electronicdrops.com member
 * 
 * This sketch is a simple example how to send data over a period of time throught serial
 * Was designed to be used together a ESP8266. The data is send to esp8266 throught serial
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
char msg[200];

int a0,a1,a2,a3,a4,a5;
byte d2,d3,d4,d5,d8,d9,d10,d11,d12,d13;


void readdata(){

  a0 = analogRead(A0);
  a1 = analogRead(A1);
  a2 = analogRead(A2);
  a3 = analogRead(A3);
  a4 = analogRead(A4);
  a5 = analogRead(A5);

  d2 = digitalRead(2);
  d3 = digitalRead(3);
  d4 = digitalRead(4);
  d5 = digitalRead(5);
  d8 = digitalRead(8);
  d9 = digitalRead(9);
  d10 = digitalRead(10);
  d11= digitalRead(11);
  d12= digitalRead(12);
  d13= digitalRead(13);
  
}

void senddata(){

sprintf(msg, "A0=%d&A1=%d&A2=%d&A3=%d&A4=%d&A5=%d&D2=%d&D3=%d&D4=%d&D5=%d&D8=%d&D9=%d&D10=%d&D11=%d&D12=%d&D13=%d"
,a0,a1,a2,a3,a4,a5,d2,d3,d4,d5,d8,d9,d10,d11,d12,d13);

SERIAL.println(msg);
  
}

TimedTask t = TimedTask(senddata,4000);
TimedTask r = TimedTask(readdata,4000);



void setup() {

  SERIAL.begin(BAUNDRATE);

  #if DEBUG == 1  
    Serial.begin(BAUNDRATE);
    Serial.println("Initializing");
  #endif
}

void loop() {

  r.run();
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
