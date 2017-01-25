#include "ClientMessage.h"

ClientMessageClass ClientMessageClass::Get(MESSAGE msg ,char* data){
   LoggerClass::Instance()->Debugln("Entering ClientMessageClass::Get");
    
   ClientMessageClass* cmsg = new ClientMessageClass();
   cmsg->msg = msg;
   cmsg->data = data;
   
   LoggerClass::Instance()->Debugln("Exiting ClientMessageClass::Get");
   return *cmsg;
}


