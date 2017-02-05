#include "ClientMessage.h"
#include "Network.h"
#include "Config.h"
#include "SysUtils.h"
#include "ServerUtils.h"
#include "TaskRunner.h"
#include "Device.h"
#include "Logger.h"

// Local variables objects utilized in the sketch
ClientMessageClass ClientMessage;
NetworkClass Network;
SysUtilsClass SysUtils;
//ServerUtilsClass ServerUtils;
TaskRunnerClass TaskRunner;

// These are singleton objects to keep the single copy of Configuration in memory 
Logger *Logger::s_instance = 0;
Config *Config::s_instance = 0;
Device *Device::s_instance = 0;
ServerUtils *ServerUtils::s_instance = 0;

const int FAIL_REGISTER_SLEEP_INTERVAL = 10 * 1000; // 10 Seconds

/*
Subroutine:     setup()
Purpose:        This is the entry point in Arduino to initialize the device and setup some ground rules
                Steps Taken
                ===========12.5
                1) Call Network.Connect()
                    a. Network.Connect() checks for available Configuration on the SPIFFS system
                    b. If no configuration found then Device tries to connect to DEFAULT WiFi AP ($DEVICE_DISCOVERY$ with passkey= admin@12345)
                    c. It keeps retrying until a connection to AP is made, at this point a Hotspot can be created 
                        via a Phone or Laptop with same configuration to allow the device to connect to server.
*/

void setup() {
    //pinMode(LED_BUILTIN, OUTPUT); 
    // Attempt to connect to WiFi from the WiFi config pool defined in the device.json
    while(!Network.IsConnected)
        Network.Connect();
}


/*
Subroutine:     loop()
Purpose:        This is the main "loop" subroutine which is at the heart of the Arduino
                Steps Taken
                ===========
                1) Double check if WiFi is connected
                2) Check if Device is registered to the server
                    a. If not registered, then Register the device to the server
                    b. Registration call will return the latest device.json for the device, which is saved in SPIFFS
                    c. If alredy registered then check if registration is still valid, renew the lease from server
                    d. Renewing the lease or initial registration will return the server time stamp and heartbeat interval along with server endpoint Url(s)
                3) Sleep until heartbeat interval is not triggered
                4) Send a Heartbeat to the server and get the list of pending tasks from the server
                5) Perform the task and report the result back to server, if more tasks are available then keep fetching until the server tasks queue has been cleared
                6) Go to Step 3
*/

void loop() {

    // Check if still connected, otherwise attempt to reconnect
    if(!Network.Connect())
        return;
    
    
    // In case its already connected, continue

    // Check if Device is registered to server and has valid DeviceId
    // Sleep for 10 seconds and Exit loop() in case of failure to register 

    if(Device::Instance()->Register()){
        Logger::Instance()->Debug("Device Id: ");
        Logger::Instance()->Debugln(Device::Instance()->DeviceId);

        // Send a heart beat to the server and execute the command returned by server
        TaskRunner.Run(ServerUtils::Instance()->SendMessage(ClientMessage.Get(MESSAGE::HEART_BEAT)));
        //delay(Device::Instance()->HeartBeatInterval);
    }
    else{
        delay(FAIL_REGISTER_SLEEP_INTERVAL);
        return;
    }


}
