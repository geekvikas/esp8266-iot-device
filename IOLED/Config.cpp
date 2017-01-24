

/*
*/

#include "Config.h"

bool ConfigClass::__LoadConfig()
{
  Logger.Debugln("Entering ConfigClass::__LoadConfig");
   
  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "r");
  if (!configFile) {
    Logger.Debugln("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Logger.Debugln("Config file size is too large");
    return false;
  }

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Logger.Debugln("Failed to parse config file");
    return false;
  }

  AP_NAME = json["apName"];
  AP_PWD = json["apPwd"];

  // Real world application would store these values in some variables for
  // later use.

  Logger.Debug("Loaded AP Name: ");
  Logger.Debugln(AP_NAME);
  Logger.Debug("Loaded AP Password: ");
  Logger.Debugln(AP_PWD);

  Logger.Debugln("Exiting ConfigClass::__LoadConfig");
  
  return true;
  
}

bool ConfigClass::__SaveDefaultConfig(){
  Logger.Debugln("Entering ConfigClass::__SaveDefaultConfig");
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["apName"] = __AP_NAME;
  json["apPwd"] = __AP_PWD;

  File configFile = SPIFFS.open(CONFIG_FILE_NAME, "w");
  if (!configFile) {
    Logger.Debugln("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  Logger.Debugln("Exiting ConfigClass::__SaveDefaultConfig");
  return true;
}

void ConfigClass::Init()
{
  Logger.Debugln("Entering ConfigClass::Init");
  if(!__LoadConfig()){
    Logger.Debugln("ConfigClass::Init - Missing Config. Saving Default Config");
    __SaveDefaultConfig();
    __LoadConfig();
  }
  
  Logger.Debugln("Exiting ConfigClass::Init");
  
}

bool ConfigClass::Update()
{
    Logger.Debugln("Entering ConfigClass::Update");
    
    Logger.Debugln("Exiting ConfigClass::Update");
    return false;
}

ConfigClass Config;
