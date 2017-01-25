#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "ClientMessage.h"  
#include "Task.h"
#include "Logger.h"  
#include "Config.h"  
#include <ESP8266HTTPClient.h>

class ServerUtilsClass {
private:
  HTTPClient __http;
public:
	const char* GetTime();
 	TaskClass SendMessage(ClientMessageClass);
};

#endif
