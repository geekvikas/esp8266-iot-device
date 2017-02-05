/*
*/

#include "ServerUtils.h"

unsigned int ServerUtilsClass::GetTime()
{
    
    Logger::Instance()->Debugln("Entering ServerUtilsClass::GetTime");
    unsigned int retVal  = 0;
    Logger::Instance()->Debugln(Config::Instance()->Get("serverTimeUrl"));
    __http.begin(Config::Instance()->Get("serverTimeUrl"));
    int httpCode = __http.GET();
    if(httpCode == HTTP_CODE_OK) {
        String payload = __http.getString();
        if(payload) 
          retVal = atol(payload.c_str());
        
    }
    __http.end();
    Logger::Instance()->Debugln("Exiting ServerUtilsClass::GetTime");
    return retVal;
}


TaskClass ServerUtilsClass::SendMessage(ClientMessageClass msg)
{
    TaskClass t;
    
    Logger::Instance()->Debugln("Entering ServerUtilsClass::SendMessage");
    
    Logger::Instance()->Debugln("Exiting ServerUtilsClass::SendMessage");
    
    return t;
}


