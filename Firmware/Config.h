#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>
#include <FS.H>
#include "Logger.h"
//#include "Network.h"


enum CONFIG_KEY{AP_NAME,AP_KEY,EP_URL};

class Config {
    
/*
Sample JSON Config file
{"AP_NAME":"Eshanya","AP_KEY":"Eshanya2013","EP_URL":"http://10.0.0.221"}

*/
private:
    String CONFIG_VALUE[3] = {"AP_NAME","AP_KEY","EP_URL"};
    
    String CONFIG_FILE_NAME = "/default.config";
    bool __IsValid();
    bool __SaveDefaultConfig();
    static Config *s_instance;
    
    
public:
    
    String DEFAULT_AP_NAME = "$DEVICE_DISCOVERY$";
    String DEFAULT_AP_KEY = "admin@12345";
    String DEFAULT_EP_URL = "http://dev.idnno.com/api/v1/device";
    static Config *Instance()
    {
          if (!s_instance)
            s_instance = new Config;
          return s_instance;
    }
    String Get(CONFIG_KEY);
    bool FactoryReset();
    bool UpdateConfig(String);

};

#endif
