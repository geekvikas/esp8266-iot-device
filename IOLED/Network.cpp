#include "Network.h"


bool NetworkClass::Connect()
{
    
    LoggerClass::Instance()->Debugln("Entering NetworkClass::Connect");
    
    // Return true if its already connected
    if(__WiFiMulti.run() == WL_CONNECTED){
      IsConnected = true;
      LoggerClass::Instance()->Debugln("NetworkClass::Connect - Connected");
      return IsConnected;
    }
    
    if(!ConfigClass::Instance()->Get("apName")){
      IsConnected = false;
      LoggerClass::Instance()->Debugln("Error: Missing Network Config!");
      return IsConnected;
    }

    LoggerClass::Instance()->Debug("Trying to connect to ...");
    LoggerClass::Instance()->Debugln(ConfigClass::Instance()->Get("apName"));
    
    __WiFiMulti.addAP(ConfigClass::Instance()->Get("apName"), ConfigClass::Instance()->Get("apPwd"));
    //pinMode(LED_BUILTIN, OUTPUT); 
    //Wait till we connect to the WiFi
    while(__WiFiMulti.run() != WL_CONNECTED) {
      LoggerClass::Instance()->Debug(".");
      //sleep for 1 seconds while we connect to WiFi and simulate by blinking the BUILTIN light
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
      delay(500);                      // Wait for a second
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
      delay(500);     
    }

    if(__WiFiMulti.run() == WL_CONNECTED){
      IsConnected = true;
      LoggerClass::Instance()->Debugln("Connected to WiFi");
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW to show that we are connected now
    }
    else
      IsConnected = false;

    // If the current configuration has DEFAULT AP NAME or not Connected to WiFi then set the IsDefaultAP = true
    if(ConfigClass::Instance()->Get("apName") == ConfigClass::Instance().DEFAULT_AP_NAME || (!IsConnected))
      IsDefaultAP = true;

    LoggerClass::Instance()->Debugln("Exiting NetworkClass::Connect");
    return IsConnected;
}

