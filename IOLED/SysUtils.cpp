/*
*/

#include "SysUtils.h"



void SysUtils::PlayLEDCode(LEDCODE ledCode)
{
    //Logger::Instance()->Debugln("Entering SysUtils::PlayLEDCode");
    String pattern = LEDCODE_Value[ledCode];
    return LEDController::Instance()->PlayPattern(LED_BUILTIN, pattern, 0);
    //Logger::Instance()->Debugln("Exiting SysUtils::PlayLEDCode");
    
}

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
