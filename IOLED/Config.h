#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>
#include <FS.H>
#include "Logger.h"
//#include "Network.h"

class ConfigClass {
    

private:
    static ConfigClass *s_instance;
    LoggerClass Logger;
    const char* CONFIG_FILE_NAME = "/device2.json";
    const char* __AP_NAME = "$DEVICE_DISCOVERY$";
    const char* __AP_PWD = "admin@12345";
    const char* __SERVER_TIME_URL = "http://172.20.10.4:3000/api/getTime";
    bool __IsValid();
    bool __SaveDefaultConfig();
    
    
public:
   
   static ConfigClass *Instance()
    {
        if (!s_instance)
          s_instance = new ConfigClass;
        return s_instance;
    }
  const char* Get(const char*);
	bool Update();
};

#endif
