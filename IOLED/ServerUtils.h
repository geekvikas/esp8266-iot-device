#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "Task.h"
#include "ClientMessage.h"
#include "Config.h"
#include "Logger.h"
#include <ESP8266HTTPClient.h>

class ServerUtilsClass {
private:
  HTTPClient __http;
  ConfigClass Config;
public:
	unsigned int GetTime();
	TaskClass SendMessage(ClientMessageClass);
};

#endif
