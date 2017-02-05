/*
*/


#include "Device.h"

bool Device::Register()
{
    Logger::Instance()->Debugln("Entering DeviceClass::Register");
    
    if(RegisterCheckSkipCount<RegisterCheckSkipLimit){
        Logger::Instance()->Debugln("DeviceClass::Register - Valid Registration");
        RegisterCheckSkipCount++;
    }
    else{
        Logger::Instance()->Debugln("DeviceClass::Register - Registration Renew Complete");
        RegisterCheckSkipCount = 0;
        DeviceId += 'X';
    }
    
    
    Logger::Instance()->Debugln("Exiting DeviceClass::Register");    
    
    return true;
}
