#include "ClientMessage.h"

ClientMessageClass ClientMessageClass::Get(MESSAGE msg ,char* data){
   Logger.Debugln("Entering ClientMessageClass::Get");
    
   ClientMessageClass* cmsg = new ClientMessageClass();
   cmsg->msg = msg;
   cmsg->data = data;
   
   Logger.Debugln("Exiting ClientMessageClass::Get");
   return *cmsg;
}


