/*
*/

#include "ServerUtils.h"

unsigned int ServerUtilsClass::GetTime()
{
    
    Logger.Debugln("Entering ServerUtilsClass::GetTime");
    unsigned int retVal = 0;
    __http.begin(Config.SERVER_TIME_URL);
    int httpCode = __http.GET();
    if(httpCode == HTTP_CODE_OK) {
        String payload = __http.getString();
        if(payload) 
          retVal = atol(payload.c_str());
    }
    __http.end();
    Logger.Debugln("Exiting ServerUtilsClass::GetTime");
    return retVal;
}


TaskClass ServerUtilsClass::SendMessage(ClientMessageClass msg)
{
    TaskClass t;
    
    Logger.Debugln("Entering ServerUtilsClass::SendMessage");
    
    Logger.Debugln("Exiting ServerUtilsClass::SendMessage");
    
    return t;
}


