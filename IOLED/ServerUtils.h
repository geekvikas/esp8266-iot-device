#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "Task.h"
#include "ClientMessage.h"  
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
	
	String GenerateMessage(ClientMessageClass);
	Task JsonToTask(String);
	static ServerUtils *Instance()
	{
			if (!s_instance)
				s_instance = new ServerUtils;
			return s_instance;
	}
	unsigned int GetTime();
 	Task SendMessage(ClientMessageClass);
	
};

#endif
