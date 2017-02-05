#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "ClientMessage.h"  
#include "Task.h"
#include "Logger.h"  
#include "Config.h"  
#include "Device.h"  
#include "DeviceInfo.h"  
#include "Http.h"

class ServerUtils {
private:
  HTTPClient __http;
	static ServerUtils *s_instance;
public:
	static ServerUtils *Instance()
	{
			if (!s_instance)
				s_instance = new ServerUtils;
			return s_instance;
	}
	unsigned int GetTime();
 	TaskClass SendMessage(ClientMessageClass);
};

#endif
