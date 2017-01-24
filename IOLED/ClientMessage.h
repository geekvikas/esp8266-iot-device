#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H
#include "Logger.h"

enum MESSAGE{HEART_BEAT};

class ClientMessageClass {
public:
	MESSAGE msg;
  char* data; 

  ClientMessageClass Get(MESSAGE,char*);
};
extern ClientMessageClass ClientMessage;
#endif
