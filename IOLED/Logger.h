#ifndef LOGGER_H
#define LOGGER_H
#include "GlobalConstants.h"
#include <fs.h>

class Logger {
private:
    const char* LOG_FILE_NAME = "/debug.log";
    File logFile;
    static Logger *s_instance;

public:
    
    Logger();
    ~Logger();
    #define DEBUG Serial
  	void Error(const char*);
    void Errorln(const char*);
    void Debug(const char*);
    void Debugln(const char*);
    void Debugln(String msg);

    static Logger *Instance()
    {
        if (!s_instance)
          s_instance = new Logger;
        return s_instance;
    }

    int ErrorCode;

};

#endif
