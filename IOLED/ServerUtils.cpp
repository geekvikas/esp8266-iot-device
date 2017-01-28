/*
*/

#include "ServerUtils.h"

unsigned int ServerUtilsClass::GetTime()
{
    
    LoggerClass::Instance()->Debugln("Entering ServerUtilsClass::GetTime");
    unsigned int retVal  = 0;
    LoggerClass::Instance()->Debugln(ConfigClass::Instance()->Get("serverTimeUrl"));
    __http.begin(ConfigClass::Instance()->Get("serverTimeUrl"));
    int httpCode = __http.GET();
    if(httpCode == HTTP_CODE_OK) {
        String payload = __http.getString();
        if(payload) 
          retVal = atol(payload.c_str());
        
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


