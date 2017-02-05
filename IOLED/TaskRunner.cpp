/*
*/


#include "TaskRunner.h"
const int MAX_SLEEP_TIME = 3600000;
const int MIN_SLEEP_TIME = 5000;

void TaskRunnerClass::Run(TaskClass task)
{
    int sleepInterval = MIN_SLEEP_TIME;
    Logger::Instance()->Debugln("Entering TaskRunnerClass::Run");
    switch(task.type){

        case TASK::FWUPDATE:
            Logger::Instance()->Debugln("FW Update Required");
            // TODO : Update the FW
            break;

        case TASK::SLEEP:
            sleepInterval = task.value;
            if(!(sleepInterval>=MIN_SLEEP_TIME && sleepInterval<= MAX_SLEEP_TIME))
                sleepInterval = MIN_SLEEP_TIME; // In case of invalid time or no time specified, sleep for least amount 
            
            Logger::Instance()->Debugln("Sleep command received...going to snooze");
            delay(sleepInterval);      
            Logger::Instance()->Debugln("Woke up from Sleep");
            
            break;

        case TASK::REBOOT:
            Logger::Instance()->Debugln("Reboot required");
            // TODO : Reboot the system
            break;

        case TASK::LED:
            Logger::Instance()->Debugln("LED Command received");
            // TODO : LED Control Logic here
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
