
/* 2018-04-17
 * Danilo Queiroz Barbosa
 * electronicdrops.com member
 * 
 * This sketch is a simple example how to send data via JSON
 * This sketch version sends esp8266 data combined the data arrived from Serial.
 * 
 * The data came from Serial and esp8266 relays the data to the server. The response is send back to Serial.
 * 
  */


#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
 

#define DEBUG  1

const char * server_address = "192.168.0.106";
const int    server_port    = 2121;
const char * server_uri     = "/monitor";


String device_ip;
String device_mac;
String device_name;


// function from https://github.com/esp8266/Arduino/issues/313
String getMacAddress(){
   
  byte mac[6]; 
  byte mac_reversed[6]; 
  
  WiFi.macAddress(mac); 
  
  for(int idx = 0; idx<6; idx++){ 
    mac_reversed[idx] = mac[6-idx]; 
  } 
    
  String cMac = ""; 
  for (int i = 0; i < 6; ++i){ 
   
    if (mac_reversed[i] < 0x10){ 
        cMac += "0";
    }         
    cMac += String(mac_reversed[i],HEX); 
    if(i < 5) 
      cMac += ":";  // put : or - if you want byte delimiters 
  } 
  cMac.toUpperCase(); 
  return cMac; 
}


//https://arduinojson.org/doc/tricks/
void merge(JsonObject& dest, const JsonObject& src) {
   for (auto kvp : src) {
     dest[kvp.key] = kvp.value;
   }
}



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

    device_ip = WiFi.localIP().toString();
    device_mac = getMacAddress();
    device_name = "sensor_test";
    

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
  String json_info;

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
   * MOUNTING JSON
   * 
   */

  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonObject& device = root.createNestedObject("device");
// //  values = root.createNestedObject("values");
//
   device["name"]= device_name;
   device["ip"]  = device_ip;
   device["mac"] = device_mac;

//   root.printTo(json_info);

    JsonObject& values = jsonBuffer.parseObject(msg);

    merge(root,values);

   root.printTo(json_info);

  

//  /*
//   * PARTE 03 - CRIA CONEXAO COM O SERVIDOR
//   */
//
     http.begin(server_address, server_port, server_uri);
     http.addHeader("Content-Type","application/json");
     int httpCode = http.POST(json_info);


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
