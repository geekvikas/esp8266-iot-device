#ifndef DEVICE_H
#define DEVICE_H
#include "ClientMessage.h"
#include "ServerUtils.h"
#include "TaskRunner.h"
#include "Task.h"
#include "Logger.h"
#include "DeviceInfo.h"


class Device {
private:
	ClientMessageClass ClientMessage;
	static Device *s_instance;
	unsigned int RegisterCheckSkipCount = 10;
	const unsigned int RegisterCheckSkipLimit = 10;

public:
	bool Register();
	String GetDeviceInfo();
	String DeviceId;
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
