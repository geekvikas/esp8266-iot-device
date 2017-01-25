#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "depends.h"

void setup() {
    
    // Look up for Configuration file, if exists then load the configurations else save the default Configuration file
    // TODO - Remove this commend and code later. No longer required as this is handled by Constructor
    // Config.Init(); 

    // Attempt to connect to WiFi from the WiFi config pool
    Network.Connect();

    // Look up for latest config from the server and upload the local config file
    // If new Config file found then reconnect the Network with updated config file
    if(Config.Update())
      Network.Connect();

    // Update the System time from the server
    SysUtils.UpdateTime(ServerUtils.GetTime());
    
}

void loop() {
    Network.Connect();
    ServerUtils.GetTime();
    // Send a heart beat to the server and execute the command returned by server
    TaskRunner.Run(ServerUtils.SendMessage(ClientMessage.Get(MESSAGE::HEART_BEAT,'\0')));

}
