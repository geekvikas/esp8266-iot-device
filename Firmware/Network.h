#ifndef NETWORK_H
#define NETWORK_H
#include "Logger.h"
#include "SysUtils.h"
#include "Config.h"
#include <ESP8266WiFiMulti.h>

class NetworkClass {
private:
  ESP8266WiFiMulti __WiFiMulti;
public:
	bool Connect();
  bool IsConnected = false;
  bool IsDefaultAP = true;
};

#endif
