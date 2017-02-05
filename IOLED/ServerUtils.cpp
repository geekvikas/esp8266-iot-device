/*
*/

#include "ServerUtils.h"
Http *Http::s_instance = 0;

// unsigned int ServerUtils::GetTime()
// {
    
//     Logger::Instance()->Debugln("Entering ServerUtils::GetTime");
//     unsigned int retVal  = 0;
//     Logger::Instance()->Debugln(Config::Instance()->Get(CONFIG_KEY::EP_URL));
    
//     String payload = Http::Instance()->Get(Config::Instance()->Get(CONFIG_KEY::EP_URL));
//     if(payload) 
//         retVal = atol(payload.c_str());

//     Logger::Instance()->Debugln("Exiting ServerUtils::GetTime");
//     return retVal;
// }


TaskClass ServerUtils::SendMessage(ClientMessageClass msg)
{
    TaskClass t;
    String devInfo = DEVICE_VERSION_INFO;
    devInfo.replace("DEVICE_INFO_PLACEHOLDER",Device::Instance()->GetDeviceInfo());



    Logger::Instance()->Debugln("Entering ServerUtils::SendMessage");

    
    Http::Instance()->Post(Config::Instance()->Get(CONFIG_KEY::EP_URL),devInfo);

    Logger::Instance()->Debugln("Exiting ServerUtils::SendMessage");
    
    return t;
}


