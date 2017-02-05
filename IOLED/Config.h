#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>
#include <FS.H>
#include "Logger.h"
//#include "Network.h"


enum CONFIG_KEY{AP_NAME,AP_KEY,EP_URL};

class Config {
    

private:
    String CONFIG_VALUE[3] = {"AP_NAME","AP_KEY","EP_URL"};
    static Config *s_instance;
    const char* CONFIG_FILE_NAME = "/device.config";
    bool __IsValid();
    bool __SaveDefaultConfig();
    
    
public:

    const char* DEFAULT_AP_NAME = "$DEVICE_DISCOVERY$";
    const char* DEFAULT_AP_KEY = "admin@12345";
    const char* DEFAULT_EP_URL = "https://dev.idnno.com/";
    static Config *Instance()
    {
          if (!s_instance)
            s_instance = new Config;
          return s_instance;
    }
    const char* Get(CONFIG_KEY);
    bool Update();
};

#endif
