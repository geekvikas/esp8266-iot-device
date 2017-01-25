#include "ClientMessage.h"
#include "Network.h"
#include "Config.h"
#include "SysUtils.h"
#include "ServerUtils.h"
#include "TaskRunner.h"
#include "Logger.h"


ClientMessageClass ClientMessage;
NetworkClass Network;
SysUtilsClass SysUtils;
ServerUtilsClass ServerUtils;
TaskRunnerClass TaskRunner;
LoggerClass *LoggerClass::s_instance = 0;
ConfigClass *ConfigClass::s_instance = 0;

void setup() {
    

    
    // Attempt to connect to WiFi from the WiFi config pool
    Network.Connect();

    // Look up for latest config from the server and upload the local config file
    // If new Config file found then reconnect the Network with updated config file
    if(ConfigClass::Instance()->Update())
      Network.Connect();

    // Update the System time from the server
    SysUtils.UpdateTime(atoi(ServerUtils.GetTime()));
    
}

void loop() {
    const char * timeVal;
    LoggerClass::Instance()->Debug("AP Name: ");
    LoggerClass::Instance()->Debugln(ConfigClass::Instance()->Get("apName"));
    
    Network.Connect();
    timeVal = ServerUtils.GetTime();
    
    if(timeVal){
      LoggerClass::Instance()->Debug("Server Time: ");
      LoggerClass::Instance()->Debugln(timeVal);
    }
    // Send a heart beat to the server and execute the command returned by server
    TaskRunner.Run(ServerUtils.SendMessage(ClientMessage.Get(MESSAGE::HEART_BEAT,'\0')));

}
