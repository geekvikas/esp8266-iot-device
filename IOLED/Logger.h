#ifndef LOGGER_H
#define LOGGER_H
#include "globalConstants.h"
#include "FS.h"

class LoggerClass {
private:
    const char* LOG_FILE_NAME = "/debug.log";
    File logFile;
    #define DEBUG Serial
public:
    LoggerClass();
    ~LoggerClass();
  	void Log(char&);
};
extern LoggerClass Logger;
#endif
