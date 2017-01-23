#ifndef SERVERUTILS_H
#define SERVERUTILS_H
#include "Task.h"

class ServerUtilsClass {
public:
	unsigned int GetTime();
	Task SendMessage();
};
extern ServerUtilsClass ServerUtils;
#endif
