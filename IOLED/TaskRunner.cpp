/*
*/


#include "TaskRunner.h"
const int MAX_SLEEP_TIME = 3600000;
const int MIN_SLEEP_TIME = 5000;

void TaskRunnerClass::Run(Task task)
{
    int sleepInterval = MIN_SLEEP_TIME;
    Logger::Instance()->Debugln("Entering TaskRunnerClass::Run");
    switch(task.type){

        case TASK::FWUPDATE:
            Logger::Instance()->Debug("FW update required, FW download URL: ");
            Logger::Instance()->Debugln(task.data);
            // TODO : Update the FW
            delay(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            break;
      
        case TASK::CNFGUPDATE:
            Logger::Instance()->Debug("Config update required, Config download URL: ");
            Logger::Instance()->Debugln(task.data);
            // TODO : Update the Config
            delay(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            break;
      
        case TASK::SLEEP:
            sleepInterval = task.value;
            if(sleepInterval<MIN_SLEEP_TIME || sleepInterval>MAX_SLEEP_TIME)
                sleepInterval = MIN_SLEEP_TIME; // In case of invalid time or no time specified, sleep for least amount 
            
            Logger::Instance()->Debugln("Sleep command received...going to snooze");
            delay(sleepInterval);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            
            break;

        case TASK::REBOOT:
            Logger::Instance()->Debugln("Rebooting...");
            sleepInterval = task.value;
            if(sleepInterval>0 && sleepInterval<MAX_SLEEP_TIME)
                delay(sleepInterval);
            ESP.restart();
            break;

        case TASK::LED:
            Logger::Instance()->Debugln("LED Command received, playing the pattern...");
            LED.PlayPattern(LED_BUILTIN,task.data,task.value);
            Logger::Instance()->Debugln("done playing the LED pattern... time for a quick snooze");
            delay(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up...");
            break;

        case TASK::NOP:
            // No operation is required, continue in next loop
            // Not recommended, sleep atleast minimum interval
            Logger::Instance()->Debugln("NOP Received...going to quick snooze");
            delay(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up from NOP snooze");
            break;

        default:
            // No operation is required, continue in next loop
            // Not recommended, sleep atleast minimum interval
            Logger::Instance()->Debugln("No Response Received...going to quick snooze");
            delay(MIN_SLEEP_TIME);      
            Logger::Instance()->Debugln("Woke up...");
            break;

    }
    
    Logger::Instance()->Debugln("Exiting TaskRunnerClass::Run");    
}
