#define DEBUG 1
#define USE_SOFTWARE_SERIAL 1
#define  BAUNDRATE 9600


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

const int MAX_BUFFER = 15;

char buff[MAX_BUFFER];

void setup() {

    SERIAL.begin(BAUNDRATE);

  #if DEBUG == 1  
    Serial.begin(BAUNDRATE);
    Serial.println("Initializing");
  #endif

}

void loop() {
  int index = 0;
  char c;
  int value;
  
 /*
 * PART 01 -- RECEIVING DATA
 */

  if (SERIAL.available() > 0) {

    while (SERIAL.available()) {
      c = SERIAL.read();

   delay(1);
     if ((c != '\r' && c!= '\n') && index < MAX_BUFFER) {
         buff[index++] = c;
      } 



      if (c == '\n' && index > 0){
        value = atoi(buff);
        Serial.println(value);
        index = 0;

       for (int i = 0; i < MAX_BUFFER; i++) {
       buff[i] = '\0';
    }
      }

    }

    #if DEBUG == 1
     Serial.println(buff);
    #endif
  }
}
