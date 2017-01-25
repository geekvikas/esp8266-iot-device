#ifndef LOGGER_H
#define LOGGER_H
#include "GlobalConstants.h"
#include <fs.h>

class LoggerClass {
private:
    static LoggerClass *s_instance;
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
    static LoggerClass *Instance()
    {
        if (!s_instance)
          s_instance = new LoggerClass;
        return s_instance;
    }
};

#endif
