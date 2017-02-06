/*
*/

#include "SysUtils.h"

void SysUtils::Sleep(unsigned int interval)
{
    //Logger::Instance()->Debugln("Entering SysUtils::Sleep");
    delay(interval);
    //Logger::Instance()->Debugln("Exiting SysUtils::Sleep");
    
}

void SysUtils::Restart()
{
    Logger::Instance()->Debugln("Entering SysUtils::Restart");
    ESP.restart();          // Software RESET
}

void SysUtils::Shutdown()
{
    Logger::Instance()->Debugln("Entering SysUtils::Shutdown");
    ESP.deepSleep(0);       // Sleep forever
}
