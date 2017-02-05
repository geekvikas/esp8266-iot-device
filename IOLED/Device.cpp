/*
*/


#include "Device.h"

bool Device::Register()
{
    Logger::Instance()->Debugln("Entering DeviceClass::Register");
    
    if(RegisterCheckSkipCount<RegisterCheckSkipLimit){
        Logger::Instance()->Debugln("DeviceClass::Register - Registration has not expired");
        RegisterCheckSkipCount++;
    }
    else{
        Logger::Instance()->Debugln("DeviceClass::Register - Registration Renew Complete");
        RegisterCheckSkipCount = 0;
        
        TaskClass task = ServerUtils::Instance()->SendMessage(ClientMessage.Get(MESSAGE::REGISTER));
        
    }
    
    
    Logger::Instance()->Debugln("Exiting DeviceClass::Register");    
    
    return true;
}


String Device::GetFirmwareInfo()
{
    return DEVICE_FIRMWARE_INFO;
}

String Device::GetDeviceInfo()
{
  String retVal = "";
  //return retVal;
         retVal = retVal + "{";
         retVal = retVal +    "\"vcc\":\"" + ESP.getVcc() + "\",";
         retVal = retVal +    "\"freeHeap\":\"" + ESP.getFreeHeap() + "\",";
         retVal = retVal +    "\"bootMode\":\"" + ESP.getBootMode() + "\",";
         retVal = retVal +    "\"cpuFreq\":\"" + ESP.getCpuFreqMHz() + "\",";
         retVal = retVal +    "\"chipId\":\"" + ESP.getChipId() + "\",";
         
         retVal = retVal +    "\"sdkVersion\":\"" + ESP.getSdkVersion() + "\",";
         retVal = retVal +    "\"coreVersion\":\"" + ESP.getCoreVersion() + "\",";
         retVal = retVal +    "\"bootVersion\":\"" + ESP.getBootVersion() + "\",";

         retVal = retVal +    "\"flashChipId\":\"" + ESP.getFlashChipId() + "\",";
         retVal = retVal +    "\"flashChipRealSize\":\"" + ESP.getFlashChipRealSize() + "\",";
         retVal = retVal +    "\"flashChipSize\":\"" + ESP.getFlashChipSize() + "\",";
         retVal = retVal +    "\"flashChipSpeed\":\"" + ESP.getFlashChipSpeed() + "\",";
         retVal = retVal +    "\"flashChipMode\":\"" + ESP.getFlashChipMode() + "\",";
         retVal = retVal +    "\"flashChipSizeByChipId\":\"" + ESP.getFlashChipSizeByChipId() + "\",";
         
         retVal = retVal +    "\"sketchSize\":\"" + ESP.getSketchSize() + "\",";
         retVal = retVal +    "\"sketchMD5\":\"" + ESP.getSketchMD5() + "\",";

         retVal = retVal +    "\"resetReason\":\"" + ESP.getResetReason() + "\",";
         retVal = retVal +    "\"resetInfo\":\"" + ESP.getResetInfo() + "\"";

         retVal = retVal + "}";

  return retVal;
}