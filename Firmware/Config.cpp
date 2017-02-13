#include "Config.h"

bool Config::__IsValid()
{
  Logger::Instance()->Debugln("Entering Config::__IsValid");
   
  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file");
    return false;
  }
    
  Logger::Instance()->Debugln("Exiting Config::__IsValid");
  
  return true;
  
}

bool Config::__SaveDefaultConfig(){
  Logger::Instance()->Debugln("Entering Config::__SaveDefaultConfig");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json[CONFIG_VALUE[CONFIG_KEY::AP_NAME]] = DEFAULT_AP_NAME;
  json[CONFIG_VALUE[CONFIG_KEY::AP_KEY]] = DEFAULT_AP_KEY;
  json[CONFIG_VALUE[CONFIG_KEY::EP_URL]] = DEFAULT_EP_URL;
  

  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "w");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  Logger::Instance()->Debugln("Exiting Config::__SaveDefaultConfig");
  return true;
}

bool Config::UpdateConfig(String config){
  
  Logger::Instance()->Debugln("Entering Config::UpdateConfig");

  Logger::Instance()->Debugln(config);

  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(config);

  String new_apName = String((const char *)root[CONFIG_VALUE[AP_NAME]]);
  String new_apKey = String((const char *)root[CONFIG_VALUE[AP_KEY]]);
  String new_epURL = String((const char *)root[CONFIG_VALUE[EP_URL]]);

  if(!(new_apName.length()>0 && new_apKey.length()>0 && new_epURL.length()>0)){
    Logger::Instance()->Debugln("Config::UpdateConfig - Invalid configuration provided");
    return false;
  }

  if(new_apName == Get(AP_NAME) && new_apKey == Get(AP_KEY) && new_epURL == Get(EP_URL)){
    Logger::Instance()->Debugln("Config::UpdateConfig - No Change Required");
    return true;
  }
  
  
  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "w");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file for writing");
    return false;
  }

  root.printTo(configFile);
  Logger::Instance()->Debugln("Exiting Config::UpdateConfig");
  return true;
}

String Config::Get(CONFIG_KEY configKey)
{
  
  Logger::Instance()->Debugln("Entering Config::Get");
  
  if(!__IsValid()){
    Logger::Instance()->Debugln("Config::Init - Missing Config. Saving Default Config");
    __SaveDefaultConfig();
  }

  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    Logger::Instance()->Debugln("Failed to open config file");
    return "";
  }
    
  size_t size = configFile.size();
  if (size > 1024) {
    Logger::Instance()->Debugln("Config file size is too large");
    return "";
  }
  
  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  
  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& jsonObject = jsonBuffer.parseObject(buf.get());

  if (!jsonObject.success()) {
    Logger::Instance()->Debugln("Failed to parse config file");
    return "";
  }
  
  return jsonObject[CONFIG_VALUE[configKey]];
    
}



bool Config::FactoryReset()
{
    bool retVal = false;
    Logger::Instance()->Debugln("Entering Config::FactoryReset");
    retVal = SPIFFS.format();
    Logger::Instance()->Debugln("Exiting Config::FactoryReset");
    return retVal;
}



