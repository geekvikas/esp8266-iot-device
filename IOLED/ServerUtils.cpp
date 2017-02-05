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
    
    t = JsonToTask(response);    

    Logger::Instance()->Debugln("Exiting ServerUtils::SendMessage");
    
    return t; 
}

TaskClass ServerUtils::JsonToTask(String json){
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    TaskClass retTask;
    String taskType;
    if(root["status"]=="success")
    {
        retTask.data = String((const char *)root["message"]["data"]);
        retTask.value = root["message"]["value"];
        taskType = String(root["message"]["type"]);
        switch(taskType){
            
            /*case retTask.ToString(TASK::FWUPDATE):
                retTask.type = TASK::FWUPDATE;
            break;
            
            case TASK::LED:
                retTask.type = TASK::LED;
            break;
            
            case TASK::REBOOT:
                retTask.type = TASK::REBOOT;
            break;
            */
            case String("SLEEP"):
                retTask.type = TASK::SLEEP;
            break;
            
            case String("NOP"):
            default:
                retTask.type = TASK::NOP;
        }
    }
    return retTask;
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