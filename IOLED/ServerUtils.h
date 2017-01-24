#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "Task.h"
#include "ClientMessage.h"
#include "Logger.h"
#include <ESP8266HTTPClient.h>

class ServerUtilsClass {
private:
  HTTPClient __http;
public:
	unsigned int GetTime();
	TaskClass SendMessage(ClientMessageClass);
};
extern ServerUtilsClass ServerUtils;
#endif
