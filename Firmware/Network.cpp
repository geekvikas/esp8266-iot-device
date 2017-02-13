#include "Network.h"


bool NetworkClass::Connect()
{
    
    Logger::Instance()->Debugln("Entering NetworkClass::Connect");

    // Set the LED to OFF
    digitalWrite(LED_BUILTIN, LED_OFF); 

    // Return true if its already connected
    if(__WiFiMulti.run() == WL_CONNECTED){
      IsConnected = true;
      Logger::Instance()->Debugln("NetworkClass::Connect - Connected");
      digitalWrite(LED_BUILTIN, LED_ON);   // Turn ON the LED to show that we are connected
      return IsConnected;
    }
    
    if(!Config::Instance()->Get(CONFIG_KEY::AP_NAME)){
      IsConnected = false;
      Logger::Instance()->Debugln("Error: Missing Network Config!");
      return IsConnected;
    }

    Logger::Instance()->Debug("Trying to connect to ...");
    Logger::Instance()->Debugln(Config::Instance()->Get(CONFIG_KEY::AP_NAME));
    
    __WiFiMulti.addAP(Config::Instance()->Get(CONFIG_KEY::AP_NAME).c_str(), Config::Instance()->Get(CONFIG_KEY::AP_KEY).c_str());
    // Always add the default AP Name just in case the stored config is not contactable
    __WiFiMulti.addAP(Config::Instance()->DEFAULT_AP_NAME.c_str(), Config::Instance()->DEFAULT_AP_KEY.c_str());

    //Wait till we connect to the WiFi
    while(__WiFiMulti.run() != WL_CONNECTED) {
      Logger::Instance()->Debug(".");
      //sleep for 1 seconds while we connect to WiFi and simulate by blinking the BUILTIN light
      digitalWrite(LED_BUILTIN, LED_OFF); // Turn the LED off by making the voltage HIGH
      SysUtils::Instance()->Sleep(500);                      // Wait for a second
      digitalWrite(LED_BUILTIN, LED_ON);  // Turn the LED on by making the voltage LOW
      SysUtils::Instance()->Sleep(500);     
    }

    // If finally the WiFi connection is made then turn on the LED and set IsConnected to true
    if(__WiFiMulti.run() == WL_CONNECTED){
      IsConnected = true;
      Logger::Instance()->Debugln("Connected to WiFi");
      digitalWrite(LED_BUILTIN, LED_ON);  // Turn the LED on by making the voltage LOW to show that we are connected now
    }
    else
      IsConnected = false;

    // If the current configuration has DEFAULT AP NAME or not Connected to WiFi then set the IsDefaultAP = true
    if(Config::Instance()->Get(CONFIG_KEY::AP_NAME) == Config::Instance()->DEFAULT_AP_NAME || (!IsConnected))
      IsDefaultAP = true;

    
    Logger::Instance()->Debugln("Exiting NetworkClass::Connect");
    return IsConnected;
}

