#ifndef CONFIG_H
#define CONFIG_H
#include <ArduinoJson.h>
#include "Logger.h"

class ConfigClass {
private:
    const char* CONFIG_FILE_NAME = "/device.json";
    const char* __AP_NAME = "$DEVICE_DISCOVERY$";
    const char* __AP_PWD = "admin@12345";
    const char* __SERVER_TIME_URL = "http://dev.idnno.com:3000/api/getTime";
    
    File logFile;
    bool __LoadConfig();
    bool __SaveDefaultConfig();
public:
	void Init();
	bool Update();
  const char* AP_NAME = "";
  const char* AP_PWD = "";
  
};
extern ConfigClass Config;
#endif
