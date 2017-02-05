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

    Logger::Instance()->Debugln("Entering ServerUtils::SendMessage");

    TaskClass t;
    String packet = GenerateMessage(msg);
    String response = "";
    
    String sURL = Config::Instance()->Get(CONFIG_KEY::EP_URL);
    Logger::Instance()->Debugln(sURL);
    
    // Call the server and get the response back for parsing
    response = Http::Instance()->Post(sURL,packet);

    Logger::Instance()->Debugln("Server Response: "  + response);
    
    if(response == "{\"result\": \"success\"}"){
        t.type = TASK::SLEEP;
        t.value = 10000;
    }
        

    Logger::Instance()->Debugln("Exiting ServerUtils::SendMessage");
    
    return t; 
}


String ServerUtils::GenerateMessage(ClientMessageClass m){

    Logger::Instance()->Debugln("Entering ServerUtils::GenerateMessage");

    String deviceInfo = Device::Instance()->GetDeviceInfo();
    String firmwareInfo = Device::Instance()->GetFirmwareInfo();
    String message = "";
    String retMsg = "";
    // Create message JSON packet
    message = "{\"type\":\"" + m.ToString(m.msg) + "\",";
    if(m.data)
        message = message + "\"data\":\"" + m.data + "\"";
    else
        message = message + "\"data\":\"" + "" + "\"";
    message = message + "}";

    // Combine all JSON parts to form the packet
    retMsg = "{\"firmwareInfo\":" + firmwareInfo + ",\"deviceInfo\":" + deviceInfo + ",\"message\":" + message + "}";
    Logger::Instance()->Debugln(retMsg);
    Logger::Instance()->Debugln("Exiting ServerUtils::GenerateMessage");

    return retMsg;
    
}