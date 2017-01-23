/*
    Log file writer to log important debug output to the log file in SPIFFS
    WARNING: Be cautious and do not write everything in SPIFFS as its VERY limited in space <128kb
*/

#include "Logger.h"

LoggerClass(){
    DEBUG.begin(BAUD_RATE);
    SPIFFS.begin();
    logFile = SPIFFS.open(LOG_FILE_NAME, "w");
}

~LoggerClass(){
    if(logFile) logFile.close();
}

bool LoggerClass::Log(char &msg)
{
    if (!logFile) {
        DEBUG.println("Failed to open log file for writing");
        return false;
    }
    else{   
        logFile.println(msg);
        return true;
    }
}

LoggerClass Logger;
