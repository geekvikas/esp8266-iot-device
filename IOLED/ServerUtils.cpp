/*
*/

#include "ServerUtils.h"

const char* ServerUtilsClass::GetTime()
{
    
    LoggerClass::Instance()->Debugln("Entering ServerUtilsClass::GetTime");
    const char* retVal = '\0';
    LoggerClass::Instance()->Debugln(ConfigClass::Instance()->Get("serverTimeUrl"));
    __http.begin(ConfigClass::Instance()->Get("serverTimeUrl"));
    int httpCode = __http.GET();
    if(httpCode == HTTP_CODE_OK) {
        String payload = __http.getString();
        if(payload) 
          retVal = payload.c_str();
        LoggerClass::Instance()->Debugln(retVal);
        
    }
    __http.end();
    LoggerClass::Instance()->Debugln("Exiting ServerUtilsClass::GetTime");
    return retVal;
}


TaskClass ServerUtilsClass::SendMessage(ClientMessageClass msg)
{
    TaskClass t;
    
    LoggerClass::Instance()->Debugln("Entering ServerUtilsClass::SendMessage");
    
    LoggerClass::Instance()->Debugln("Exiting ServerUtilsClass::SendMessage");
    
    return t;
}


