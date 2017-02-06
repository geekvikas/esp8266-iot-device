/*
*/

#include "ServerUtils.h"



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


Task ServerUtils::SendMessage(ClientMessageClass msg)
{

    Logger::Instance()->Debugln("Entering ServerUtils::SendMessage");

    Task t;
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

Task ServerUtils::JsonToTask(String json){
    
    Logger::Instance()->Debugln("Entering ServerUtils::JsonToTask");
    
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    Task retTask;
    String status = String((const char *)root["status"]);
    if(status && status=="success")
    {
        String messageType = String((const char *)root["message"]["type"]);
        String messageData = String((const char *)root["message"]["data"]);
        String messageValue = String((const char *)root["message"]["value"]);
        
        retTask.data = messageData;
        retTask.value = messageValue.toInt();

        if(messageType == Task::Instance()->ToString(TASK::FW_UPDATE)){
            Logger::Instance()->Debug("Task Type: FW_UPDATE, ");
            retTask.type = TASK::FW_UPDATE;
        }
        else if(messageType == Task::Instance()->ToString(TASK::CONFIG_UPDATE)){
            Logger::Instance()->Debug("Task Type: CONFIG_UPDATE, ");
            retTask.type = TASK::CONFIG_UPDATE;
        }
        else if(messageType == Task::Instance()->ToString(TASK::FACTORY_RESET)){
            Logger::Instance()->Debug("Task Type: FACTORY_RESET, ");
            retTask.type = TASK::FACTORY_RESET;
        }        
        else if(messageType == Task::Instance()->ToString(TASK::LED)){
            Logger::Instance()->Debug("Task Type: LED, ");
            retTask.type = TASK::LED;
        }
        else if(messageType == Task::Instance()->ToString(TASK::REBOOT)){
            Logger::Instance()->Debug("Task Type: REBOOT, ");
            retTask.type = TASK::REBOOT;
        }
        else if(messageType == Task::Instance()->ToString(TASK::SHUTDOWN)){
            Logger::Instance()->Debug("Task Type: SHUTDOWN, ");
            retTask.type = TASK::SHUTDOWN;
        }
        else if(messageType == Task::Instance()->ToString(TASK::SLEEP)){
            Logger::Instance()->Debug("Task Type: SLEEP, ");
            retTask.type = TASK::SLEEP;
        }
        else if(messageType == Task::Instance()->ToString(TASK::REG_OK)){
            Logger::Instance()->Debug("Task Type: REG_OK, ");
            retTask.type = TASK::REG_OK;
        }
        else if(messageType == Task::Instance()->ToString(TASK::REG_INVALID)){
            Logger::Instance()->Debug("Task Type: REG_INVALID, ");
            retTask.type = TASK::REG_INVALID;
        }
        else{
            Logger::Instance()->Debug("Task Type: NOP, ");
            retTask.type = TASK::NOP;
        }

        Logger::Instance()->Debugln("Data: " + retTask.data);
        
    }
    Logger::Instance()->Debugln("Exiting ServerUtils::JsonToTask");
    
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
