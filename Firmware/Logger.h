#ifndef LOGGER_H
#define LOGGER_H
#include "GlobalConstants.h"
#include <fs.h>

class Logger {
private:
    String LOG_FILE_NAME = "/debug.log";
    File logFile;
    static Logger *s_instance;

public:
    
    Logger();
    ~Logger();
    #define DEBUG Serial
  	void Error(String);
    void Errorln(String);
    void Debug(String);
    void Debugln(String);
    
    static Logger *Instance()
    {
        if (!s_instance)
          s_instance = new Logger;
        return s_instance;
    }

    int ErrorCode;

};

#endif
