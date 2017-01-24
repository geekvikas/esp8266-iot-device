#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "Task.h"
#include "ClientMessage.h"

class ServerUtilsClass {
public:
	unsigned int GetTime();
	TaskClass SendMessage(ClientMessageClass);
};
extern ServerUtilsClass ServerUtils;
#endif
