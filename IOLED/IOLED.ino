#include "depends.h"

void setup() {
    
    // Look up for Configuration file, if exists then load the configurations else save the default Configuration file
    Config.Init();

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

    // Send a heart beat to the server and execute the command returned by server
    TaskRunner.Run(ServerUtils.SendCommand(Commands.HEART_BEAT));

}
