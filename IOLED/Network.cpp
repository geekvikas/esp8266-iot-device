/*
*/

#include "Network.h"

bool NetworkClass::Connect()
{
    
    Logger.Debugln("Entering NetworkClass::Connect");
    
    // Return true if its already connected
    if(__WiFiMulti.run() == WL_CONNECTED){
      Logger.Debugln("NetworkClass::Connect - Connected");
      return true;
    }
    
    if(!Config.AP_NAME){
      Logger.Debugln("Error: Missing Network Config!");
      return false;
    }

    Logger.Debug("Trying to connect to ...");
    Logger.Debugln(Config.AP_NAME);
    
    __WiFiMulti.addAP(Config.AP_NAME, Config.AP_PWD);
    //pinMode(LED_BUILTIN, OUTPUT); 
    //Wait till we connect to the WiFi
    while(__WiFiMulti.run() != WL_CONNECTED) {
      Logger.Debug(".");
      //sleep for 1 seconds while we connect to WiFi and simulate by blinking the BUILTIN light
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
      delay(500);                      // Wait for a second
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
      delay(500);     
    }

    if(__WiFiMulti.run() == WL_CONNECTED){
      Logger.Debugln("Connected to WiFi");
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW to show that we are connected now
    }
    
    Logger.Debugln("Exiting NetworkClass::Connect");
    return true;
}

