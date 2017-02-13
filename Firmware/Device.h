#ifndef DEVICE_H
#define DEVICE_H
#include <ESP8266httpUpdate.h>
#include "ClientMessage.h"
#include "ServerUtils.h"
#include "TaskRunner.h"
#include "Task.h"
#include "Logger.h"
#include "DeviceInfo.h"


class Device {
private:
	ClientMessageClass ClientMessage;
	
	unsigned int RegisterCheckSkipCount = 10;
	static Device *s_instance;
  
public:
	bool FirmwareUpdate(String);
	bool Register();
	String GetDeviceInfo();
	String GetFirmwareInfo();
	void Sleep(unsigned int);
	String DeviceId;
	unsigned int RegisterCheckSkipLimit = 10;
  unsigned int LeaseExpiry;
	unsigned int HeartBeatInterval = 1000;
	static Device *Instance()
    {
        if (!s_instance)
          s_instance = new Device;
        return s_instance;
    }
};
#endif
