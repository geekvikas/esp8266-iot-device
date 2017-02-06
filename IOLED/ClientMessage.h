#ifndef CLIENTMESSAGE_H
#define CLIENTMESSAGE_H
#include "Logger.h"

enum MESSAGE{HEART_BEAT,REGISTER};

class ClientMessageClass {
  String MESSAGE_VALUE[2] = {"HBT","REG"};
   
public:
  MESSAGE msg;
  String data; 
  ClientMessageClass Get(MESSAGE,String);
  ClientMessageClass Get(MESSAGE);
  String ToString(MESSAGE);
  
};

#endif
