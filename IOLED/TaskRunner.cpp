/*
*/


#include "TaskRunner.h"
const int MAX_SLEEP_TIME = 3600000;
const int MIN_SLEEP_TIME = 5000;

void TaskRunner::Run(Task task)
{
    int sleepInterval = MIN_SLEEP_TIME;
    Logger::Instance()->Debugln("Entering TaskRunner::Run");
    switch(task.type){

        case TASK::FW_UPDATE:
            Logger::Instance()->Debug("FW update required, FW download URL: ");
            Logger::Instance()->Debugln(task.data);
            // TODO : Update the FW
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            break;
      
        case TASK::CONFIG_UPDATE:
            Logger::Instance()->Debug("Config update required, Config download URL: ");
            Logger::Instance()->Debugln(task.data);
            // TODO : Update the Config
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            break;

        case TASK::FACTORY_RESET:
            Logger::Instance()->Debug("Factory Reset required...");
            Config::Instance()->FactoryReset();
            SysUtils::Instance()->Restart();      
            break;
      
        case TASK::SLEEP:
            sleepInterval = task.value;
            if(sleepInterval<MIN_SLEEP_TIME || sleepInterval>MAX_SLEEP_TIME)
                sleepInterval = MIN_SLEEP_TIME; // In case of invalid time or no time specified, sleep for least amount 
            
            Logger::Instance()->Debugln("Sleep command received...going to snooze");
            SysUtils::Instance()->Sleep(sleepInterval);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            
            break;

        case TASK::REBOOT:
            Logger::Instance()->Debugln("Rebooting...");
            sleepInterval = task.value;
            if(sleepInterval>0 && sleepInterval<MAX_SLEEP_TIME)
                SysUtils::Instance()->Sleep(sleepInterval);
            SysUtils::Instance()->Restart();
            break;

        case TASK::SHUTDOWN:
            Logger::Instance()->Debugln("Shuting down...");
            SysUtils::Instance()->Shutdown(); // Sleep forever in deepSleep mode
            break;

        case TASK::LED:
            Logger::Instance()->Debugln("LED Command received, playing the pattern...");
            LEDController::Instance()->PlayPattern(LED_BUILTIN,task.data,task.value);
            Logger::Instance()->Debugln("done playing the LED pattern... time for a quick snooze");
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up...");
            break;

        case TASK::REG_OK:
            Logger::Instance()->Debugln("Registration OK");
            Device::Instance()->DeviceId = task.data;
            if(task.value>0)
                Device::Instance()->RegisterCheckSkipLimit = task.value;
            
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from REG_OK snooze");
            break;
        
        case TASK::REG_INVALID:
            Logger::Instance()->Debugln("Registration INVALID");
            Device::Instance()->DeviceId = "";
            Device::Instance()->RegisterCheckSkipLimit = 0;
            
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from REG_INVALID snooze");
            break;

        case TASK::NOP:
            Logger::Instance()->Debugln("NOP Received...going to quick snooze");
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from NOP snooze");
            break;

        default:
            // No operation is required, continue in next loop
            // Not recommended, sleep atleast minimum interval
            Logger::Instance()->Debugln("No Response Received...going to quick snooze");
            SysUtils::Instance()->Sleep(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up...");
            break;

    }
    
    Logger::Instance()->Debugln("Exiting TaskRunner::Run");    
}
