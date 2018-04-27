/* 2018-04-25
 * Danilo Queiroz Barbosa
 * daniloqb@electronicdrops.com
 * electronicdrops.com member
 * 
 * This sketch is a example of sending JSON temperature data over wifi using arduino-esp8266-lm35
 */

 
#include <TimedTask.h>
#include <ArduinoJson.h>



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

const int MAX_BUFFER = 500;

char buff[MAX_BUFFER];
char msg[200];

/*
 * DECLARING SENSOR OBJECT
 */

#define DEVICE_ID  0x0035
#define DEVICE_NAME "temperature sensor"

 #include "TemperatureSensors.h"
 
TemperatureSensorLM35 sensor = TemperatureSensorLM35(A0);


void readdata(){
  sensor.update();
  }

void senddata(){

StaticJsonBuffer<200> jsonBuffer;
JsonObject& root        = jsonBuffer.createObject();
JsonArray&  devices     = root.createNestedArray("devices");
JsonObject& device_lm35 = devices.createNestedObject();

device_lm35["id"] = DEVICE_ID;
device_lm35["name"] = DEVICE_NAME;

JsonObject& values = device_lm35.createNestedObject("values");
values["temperature"] = sensor.getTemperature();


root.printTo(msg,200);


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

    sensor.begin(); //initializing sensor
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
