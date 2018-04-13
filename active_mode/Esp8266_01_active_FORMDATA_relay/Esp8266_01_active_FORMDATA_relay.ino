#include <WiFiClient.h>
#include <WiFiManager.h> 

#define DEBUG  1

const char * server_address = "192.168.0.106";
const int    server_port    = 2121;
const char * server_url     = "/api/v1/monitor";



void setup() {


  Serial.setRxBufferSize(1024);
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

  WiFiClient client;
  
  if (!client.connect(server_address, server_port)) {

    #if DEBUG == 1
     Serial.println("connection failed");
    #endif
    
    return;
  }

  client.print("POST " + String(server_url) + " HTTP/1.1\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Host: " + server_address +":" + server_port + "\r\n" + 
               "Connection: close\r\n" +
               "Content-Length:" + msg.length() + "\r\n" +
               "Connection: close\r\n" +
               "\r\n" + 
                msg + "\r\n\r\n");
  

  
  // Send the response to the client

  delay(1);
  client.stop();

  #if DEBUG == 1
   Serial.println("connection sucessfull");
  #endif
  }
    
   
}
