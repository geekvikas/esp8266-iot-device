#include "ClientMessage.h"
#include "Network.h"
#include "Config.h"
#include "SysUtils.h"
#include "ServerUtils.h"
#include "TaskRunner.h"
#include "Device.h"
#include "LEDController.h"
#include "Logger.h"

// Local variables objects utilized in the sketch
ClientMessageClass ClientMessage;
NetworkClass Network;

// These are singleton objects to keep the single copy of Configuration in memory 
SysUtils *SysUtils::s_instance = 0;
Logger *Logger::s_instance = 0;
Config *Config::s_instance = 0;
Device *Device::s_instance = 0;
ServerUtils *ServerUtils::s_instance = 0;
Http *Http::s_instance = 0;
Task *Task::s_instance = 0;
LEDController *LEDController::s_instance = 0;
TaskRunner *TaskRunner::s_instance = 0;

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
 

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // Turn Off the LED on BOOT
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
                2) Register/renew registration of the device to the server
                3) Server will return a Task which will be executed by device
                4) After the task has been executed the device will sleep for a MINIMUM interval
                5) TODO: Perform the task and report the result back to server, if more tasks are available then keep fetching until the server tasks queue has been cleared
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
        TaskRunner::Instance()->Run(ServerUtils::Instance()->SendMessage(ClientMessage.Get(MESSAGE::HEART_BEAT)));
        //delay(Device::Instance()->HeartBeatInterval);
    }
    else{
        SysUtils::Instance()->Sleep(FAIL_REGISTER_SLEEP_INTERVAL);
        return;
    }


}
