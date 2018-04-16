
/* 2018-04-15
 * Danilo Queiroz Barbosa
 * electronicdrops.com member
 * 
 * This sketch is a simple example how to send data via POST or GET html variables.
 * 
 * The data came from Serial and esp8266 relays the data to the server. The response is send back to Serial.
 * 
  */


#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
 

#define DEBUG  1

const char * server_address = "192.168.0.106";
const int    server_port    = 80;
const char * server_uri     = "/receive.php";


void setup() {



  Serial.begin(9600);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset saved settings
  //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    
    //if you get here you have connected to the WiFi

    #if DEBUG == 1
     Serial.print ( "IP address: " );
     Serial.println ( WiFi.localIP() );
     Serial.println("connected...yeey :)");
    #endif
}

void loop() {

  char c;
  String msg;
  HTTPClient http;


/*
 *  PARTE 01 - VERIFICA SE EXISTEM DADOS A SEREM ENVIADOS
 */

 if (Serial.available() > 0) { 
  

   /*
    * PART02 - PEGA OS DADOS DA SERIAL
    */
  while (Serial.available()) {
  
     char c = Serial.read();
     if (isprint(c))
       msg += c;
     delay(2);
  }

  

  /*
   * PARTE 03 - CRIA CONEXAO COM O SERVIDOR
   */

  String uri_data = server_uri;
  uri_data += "?" + msg;


     http.begin(server_address, server_port, uri_data);
    // http.addHeader("Content-Type","application/x-www-form-urlencoded");
     int httpCode = http.GET();


     if(httpCode > 0) {
      if(httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        //Serial.println("connection sucessful");
        Serial.println(payload);
      } else{
        #if DEBUG == 1
          Serial.println("connection fault");
        #endif
      }
     }

     http.end();
  
  
  
  
  }
    
   
}
