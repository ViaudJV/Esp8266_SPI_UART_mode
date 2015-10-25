

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


#include "ConfigWifi.h"
ConfigWifi Config;
MDNSResponder mdns;


String inputString = "";        // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
boolean ssid = false;           // Indicate the next string is for new ssid
boolean password = false;           // Indicate the next string is for new ssid
boolean host = false;           // Indicate the next string is for new ssid

void setup()
{
  
  char SsidAP[] = "TOTO";
  char PwdAP[] = "tatatata";
  
  WiFi.disconnect();
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(0, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  WiFi.mode(WIFI_AP);
  WiFi.softAP(SsidAP, PwdAP,6);
  //Restore the wifi config
  Config.Restore();
 

}

void loop() {
  
  Commande();
    yield();

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void Commande()
{
  
  serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete)
  {
    if( true == password)
    {
      password = false;
      if( 64 >= (inputString.length() -1))
      {
          inputString.toCharArray(Config.m_wifiKey,inputString.length());
          Serial.print("password ");
          Serial.println(Config.m_wifiKey);
      }
    }
    if( true == host)
    {
      host = false;
      if( 64 >= (inputString.length() -1))
      {
          inputString.toCharArray(Config.m_host,inputString.length());
          Serial.print("host ");
          Serial.println(Config.m_host);
      }
    }
     if( true == ssid)
    {
      ssid = false;
      if( 32 >= (inputString.length() -1))
      {
          inputString.toCharArray(Config.m_ssid,inputString.length());
          Serial.print("ssid ");
          Serial.println(Config.m_ssid);
      }
    }   
    if(!inputString.compareTo("password\n"))
    {
       Serial.println("password Detected");
      password = true;
    }

  
    if(!inputString.compareTo("save\n"))
    {
      Serial.println("sauvegarde Detected");
      Config.Save();
    }  
    
    
    if(!inputString.compareTo("ssid\n"))
    {
       Serial.println("ssid Detected");
      ssid = true;
    }  
     
    
    if(!inputString.compareTo("host\n"))
    {
       Serial.println("host Detected");
      host = true;
    }  
    
    if(!inputString.compareTo("ConfigReset\n"))
    {
     Serial.println("Reset Detected");
     WiFi.disconnect();   
     int timer = 0;
    while (WiFi.status() != WL_DISCONNECTED || timer != 20) {
    delay(500);
    Serial.print(".");
      timer++;
      }
    Config.Reset();    
    }    
    if(!inputString.compareTo("Connect\n"))
    {
       Serial.println("Begin connection");
        WiFi.begin(Config.m_ssid, Config.m_wifiKey);
        Serial.println("");
    
      // Wait for connection
       int timer = 0;
        while (WiFi.status() != WL_CONNECTED ) {
        delay(500);
        Serial.print(".");
      }
      if( timer != 20)
      {
        Serial.println("Connect Succed");
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        mdns.begin(Config.m_host, WiFi.localIP());
      }
      else
      {
              Serial.println("Connect Failed");
  
      }
    }
    
    if(!inputString.compareTo("Disconnect\n"))
    {
        WiFi.disconnect();   
         int timer = 0;
        while (WiFi.status() != WL_DISCONNECTED || timer != 20) {
        delay(500);
        Serial.print(".");
        timer++;
        }
      if( timer != 20)
      {
        Serial.println("Disconnect Succed");
        Serial.println("");
      
      }
      else
      {
              Serial.println("Connect Failed");
  
      }
    }  
      
    if(!inputString.compareTo("Config\n"))
    {
      Serial.print("ssid ");
      Serial.println(Config.m_ssid);
      Serial.print("password ");
      Serial.println(Config.m_wifiKey);
      Serial.print("host ");
      Serial.println(Config.m_host);    
    } 
    //Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
    
  }


  

}

