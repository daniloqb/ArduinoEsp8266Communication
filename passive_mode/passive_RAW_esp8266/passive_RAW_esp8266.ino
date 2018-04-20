
/* 2018-04-20
 * Danilo Queiroz Barbosa
 * electronicdrops.com member
 * 
 * This sketch is a simple example how to receive data from wifi
 * This sketch version is a bridge between data receive from wifi and send to serial. no response back
 
  */


#include <WiFiManager.h>
 

#define DEBUG  1
#define BAUNDRATE 9600

WiFiServer server(80);


void setup() {



  Serial.begin(BAUNDRATE);

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


   server.begin();
   #if DEBUG == 1
      Serial.println("Server started");
   #endif

    
}

void loop() {

  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

    // Wait until the client sends some data

  while(!client.available()){
    delay(1);
  }

    // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);

  
    
   
}
