#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H
#include "Logger.h"

enum MESSAGE{HEART_BEAT,REGISTER};

class ClientMessageClass {
public:
	MESSAGE msg;
  char* data; 

  ClientMessageClass Get(MESSAGE,char*);
  ClientMessageClass Get(MESSAGE);
};

#endif
