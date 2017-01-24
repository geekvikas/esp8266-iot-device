#include "ClientMessage.h"

ClientMessageClass ClientMessageClass::Get(MESSAGE msg ,char* data){
   ClientMessageClass* cmsg = new ClientMessageClass();
   cmsg->msg = msg;
   cmsg->data = data;
   return *cmsg;
}

ClientMessageClass ClientMessage;

