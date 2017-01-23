#ifndef DEPENDS_H
#define DEPENDS_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include "lib\\Commands.h"
#include "lib\\Config.h"
#include "lib\\GlobalConstants.h"
#include "lib\\Logger.h"
#include "lib\\Network.h"
#include "lib\\Task.h"
#include "lib\\TaskRunner.h"
#include "lib\\ServerUtils.h"
#include "lib\\SysUtils.h"

// Not using NTPTime library anymore - getting the time from HTTP Connection
//#include "NTPTime.h"

#endif