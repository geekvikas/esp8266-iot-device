#ifndef LOGGER_H
#define LOGGER_H
#include "GlobalConstants.h"
#include <fs.h>

class LoggerClass {
private:
    const char* LOG_FILE_NAME = "/debug.log";
    File logFile;
public:
    #define DEBUG Serial
    LoggerClass();
    ~LoggerClass();
  	void Error(const char*);
    void Errorln(const char*);
    void Debug(const char*);
    void Debugln(const char*);
};
extern LoggerClass Logger;
#endif
