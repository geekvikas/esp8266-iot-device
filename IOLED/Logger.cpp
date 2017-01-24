/*
    Log file writer to log important debug output to the log file in SPIFFS
    WARNING: Be cautious and do not write everything in SPIFFS as its VERY limited in space <128kb
*/

#include "Logger.h"

LoggerClass::LoggerClass(){
    DEBUG.begin(BAUD_RATE);
    SPIFFS.begin();
    logFile = SPIFFS.open(LOG_FILE_NAME, "w");
}

LoggerClass::~LoggerClass(){
    if(logFile) logFile.close();
}

void LoggerClass::Debug(const char *msg)
{
  DEBUG.print(msg);
}

void LoggerClass::Debugln(const char *msg)
{
  DEBUG.println(msg);
}


void LoggerClass::Error(const char *msg)
{
    if (!logFile) 
        Debugln("Failed to open log file for writing");
    else
        logFile.print(msg);
}


void LoggerClass::Errorln(const char *msg)
{
    if (!logFile) 
        Debugln("Failed to open log file for writing");
    else
        logFile.println(msg);
}

LoggerClass Logger;
