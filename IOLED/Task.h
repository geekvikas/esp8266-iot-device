#ifndef TASK_H
#define TASK_H
#include "Logger.h"


enum TASK{NOP,SLEEP,REBOOT,FWUPDATE,LED};

class TaskClass {
  String TASK_VALUE[5] = {"NOP","SLEEP","REBOOT","FWUPDATE","LED"};
  public:
    TASK type;
    String data;
    int value;
};
#endif
