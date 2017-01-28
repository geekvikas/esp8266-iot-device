#include "Config.h"

bool ConfigClass::__IsValid()
{
  LoggerClass::Instance()->Debugln("Entering ConfigClass::__IsValid");
   
  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    LoggerClass::Instance()->Debugln("Failed to open config file");
    return false;
  }
    
  LoggerClass::Instance()->Debugln("Exiting ConfigClass::__IsValid");
  
  return true;
  
}

bool ConfigClass::__SaveDefaultConfig(){
  LoggerClass::Instance()->Debugln("Entering ConfigClass::__SaveDefaultConfig");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["apName"] = DEFAULT_AP_NAME;
  json["apPwd"] = __AP_PWD;
  json["serverTimeUrl"] = __SERVER_TIME_URL;

  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "w");
  if (!configFile) {
    LoggerClass::Instance()->Debugln("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  LoggerClass::Instance()->Debugln("Exiting ConfigClass::__SaveDefaultConfig");
  return true;
}

const char* ConfigClass::Get(const char* configName)
{
  
  LoggerClass::Instance()->Debugln("Entering ConfigClass::Get");
  
  if(!__IsValid()){
    LoggerClass::Instance()->Debugln("ConfigClass::Init - Missing Config. Saving Default Config");
    __SaveDefaultConfig();
  }

   File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    LoggerClass::Instance()->Debugln("Failed to open config file");
    return false;
  }
    
  size_t size = configFile.size();
  if (size > 1024) {
    LoggerClass::Instance()->Debugln("Config file size is too large");
    return '\0';
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
    LoggerClass::Instance()->Debugln("Failed to parse config file");
    return '\0';
  }

  return jsonObject[configName];
    
}

bool ConfigClass::Update()
{
    LoggerClass::Instance()->Debugln("Entering ConfigClass::Update");
    
    LoggerClass::Instance()->Debugln("Exiting ConfigClass::Update");
    return false;
}



