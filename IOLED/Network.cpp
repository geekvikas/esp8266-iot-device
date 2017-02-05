#include "Network.h"


bool NetworkClass::Connect()
{
    
    Logger::Instance()->Debugln("Entering NetworkClass::Connect");

    // Set the LED to OFF
    digitalWrite(LED_BUILTIN, HIGH); 

    // Return true if its already connected
    if(__WiFiMulti.run() == WL_CONNECTED){
      IsConnected = true;
      Logger::Instance()->Debugln("NetworkClass::Connect - Connected");
      digitalWrite(LED_BUILTIN, LOW);   // Turn ON the LED to show that we are connected
      return IsConnected;
    }
    
    if(!Config::Instance()->Get("apName")){
      IsConnected = false;
      Logger::Instance()->Debugln("Error: Missing Network Config!");
      return IsConnected;
    }

    Logger::Instance()->Debug("Trying to connect to ...");
    Logger::Instance()->Debugln(Config::Instance()->Get("apName"));
    
    __WiFiMulti.addAP(Config::Instance()->Get("apName"), Config::Instance()->Get("apPwd"));
    //Wait till we connect to the WiFi
    while(__WiFiMulti.run() != WL_CONNECTED) {
      Logger::Instance()->Debug(".");
      //sleep for 1 seconds while we connect to WiFi and simulate by blinking the BUILTIN light
      digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
      delay(500);                      // Wait for a second
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
      delay(500);     
    }

    // If finally the WiFi connection is made then turn on the LED and set IsConnected to true
    if(__WiFiMulti.run() == WL_CONNECTED){
      IsConnected = true;
      Logger::Instance()->Debugln("Connected to WiFi");
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW to show that we are connected now
    }
    else
      IsConnected = false;

    // If the current configuration has DEFAULT AP NAME or not Connected to WiFi then set the IsDefaultAP = true
    if(Config::Instance()->Get("apName") == Config::Instance()->DEFAULT_AP_NAME || (!IsConnected))
      IsDefaultAP = true;

    
    Logger::Instance()->Debugln("Exiting NetworkClass::Connect");
    return IsConnected;
}

