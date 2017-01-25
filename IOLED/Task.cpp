/*
*/

#include "Task.h"

TaskClass::TaskClass()
{
    LoggerClass::Instance()->Debugln("Entering TaskClass::TaskClass");
    
    LoggerClass::Instance()->Debugln("Exiting TaskClass::TaskClass");
  
}

TaskClass::~TaskClass()
{
    LoggerClass::Instance()->Debugln("Entering TaskClass::~TaskClass");
    
    LoggerClass::Instance()->Debugln("Exiting TaskClass::~TaskClass");  
}

