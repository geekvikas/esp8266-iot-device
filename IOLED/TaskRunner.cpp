/*
*/


#include "TaskRunner.h"

void TaskRunnerClass::Run(TaskClass task)
{
    Logger.Debugln("Entering TaskRunnerClass::Run");
    
    Logger.Debugln("Exiting TaskRunnerClass::Run");    
}

TaskRunnerClass TaskRunner;
