#ifndef LOGGER_H
#define LOGGER_H
#include "globalConstants.h"
#include "FS.h"

class LoggerClass {
private:
    LoggerClass();
    const char* LOG_FILE_NAME = "/debug.log";
    File logFile;
    #define DEBUG Serial
public:
	void Log(char&);
};
extern LoggerClass Logger;
#endif
