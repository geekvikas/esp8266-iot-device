/*
    Log file writer to log important debug output to the log file in SPIFFS
    WARNING: Be cautious and do not write everything in SPIFFS as its VERY limited in space <128kb
*/

#include "Logger.h"

Logger::Logger(){
    DEBUG.begin(BAUD_RATE);
    SPIFFS.begin();
    logFile = SPIFFS.open(LOG_FILE_NAME, "w");
}

Logger::~Logger(){
    if(logFile) logFile.close();
}

void Logger::Debug(const char *msg)
{
  DEBUG.print(msg);
}

void Logger::Debugln(const char *msg)
{
  DEBUG.println(msg);
}

void Logger::Debugln(String msg)
{
  DEBUG.println(msg);
}

void Logger::Error(const char *msg)
{
    if (!logFile) 
        Debugln("Failed to open log file for writing");
    else
        logFile.print(msg);
}


void Logger::Errorln(const char *msg)
{
    if (!logFile) 
        Debugln("Failed to open log file for writing");
    else
        logFile.println(msg);
}

