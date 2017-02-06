#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>
#include <FS.H>
#include "Logger.h"
//#include "Network.h"


enum CONFIG_KEY{AP_NAME,AP_KEY,EP_URL,CONFIG_VERSION};

class Config {
    

private:
    String CONFIG_VALUE[4] = {"AP_NAME","AP_KEY","EP_URL","CONFIG_VERSION"};
    
    const char* CONFIG_FILE_NAME = "/config.json.tmp";
    bool __IsValid();
    bool __SaveDefaultConfig();
    static Config *s_instance;
    
    
public:
    
    const char* DEFAULT_AP_NAME = "$DEVICE_DISCOVERY$";
    const char* DEFAULT_AP_KEY = "admin@12345";
    const char* DEFAULT_EP_URL = "http://172.20.10.4:3000/";
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
