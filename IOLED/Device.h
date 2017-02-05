#ifndef DEVICE_H
#define DEVICE_H
#include "Logger.h"

class Device {
private:
	static Device *s_instance;
	unsigned int RegisterCheckSkipCount = 10;
	const unsigned int RegisterCheckSkipLimit = 10;
	
public:
	bool Register();
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
