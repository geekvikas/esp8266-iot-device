/*
*/

#include "ServerUtils.h"

unsigned int ServerUtilsClass::GetTime()
{
    Logger.Debugln("Entering ServerUtilsClass::GetTime");
    
    Logger.Debugln("Exiting ServerUtilsClass::GetTime");
    return 0;
}


TaskClass ServerUtilsClass::SendMessage(ClientMessageClass msg)
{
    TaskClass t;
    
    Logger.Debugln("Entering ServerUtilsClass::SendMessage");
    
    Logger.Debugln("Exiting ServerUtilsClass::SendMessage");
    
    return t;
}

ServerUtilsClass ServerUtils;
