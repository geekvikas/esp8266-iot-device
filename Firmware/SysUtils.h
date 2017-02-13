#ifndef SYSUTILS_H
#define SYSUTILS_H
#include "LedController.h"
#include "Logger.h"

enum LEDCODE{
  WIFI_CONNECTING,
  WIFI_CONNECTED,
  HTTP_SENDING,
  HTTP_ERROR,
  HTTP_SUCCESS
};

class SysUtils {
private:
	static SysUtils *s_instance;
public:
	
  String LEDCODE_Value[5] = {
        "10",       //WIFI_CONNECTING
        "1",        //WIFI_CONNECTED
        "100",      //HTTP_SENDING,
        "11110000", //HTTP_ERROR,
        "110"       //HTTP_SUCCESS
    };
  void Sleep(unsigned int);
	
  void Restart();
	
  void Shutdown();
  
  void PlayLEDCode(LEDCODE);
	
  static SysUtils *Instance()
    {
          if (!s_instance)
            s_instance = new SysUtils;
          return s_instance;
    }
};

#endif
