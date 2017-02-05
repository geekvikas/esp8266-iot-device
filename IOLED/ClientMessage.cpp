#include "ClientMessage.h"

ClientMessageClass ClientMessageClass::Get(MESSAGE msg ,char* data = '\0'){
   Logger::Instance()->Debugln("Entering ClientMessageClass::Get");
    
   ClientMessageClass* cmsg = new ClientMessageClass();
   cmsg->msg = msg;
   cmsg->data = data;
   
   Logger::Instance()->Debugln("Exiting ClientMessageClass::Get");
   return *cmsg;
}


ClientMessageClass ClientMessageClass::Get(MESSAGE msg ){
   return Get(msg,'\0');
}



