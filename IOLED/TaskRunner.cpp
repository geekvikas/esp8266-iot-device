/*
*/


#include "TaskRunner.h"

void TaskRunnerClass::Run(TaskClass task)
{
    LoggerClass::Instance()->Debugln("Entering TaskRunnerClass::Run");
    
    LoggerClass::Instance()->Debugln("Exiting TaskRunnerClass::Run");    
}
