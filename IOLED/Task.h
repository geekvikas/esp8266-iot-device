#ifndef TASK_H
#define TASK_H
#include "Logger.h"


enum TASK{NOP,SLEEP,LED,REBOOT,FWUPDATE,CNFGUPDATE};

class Task {
  private:
    static Task *s_instance;

  public:
    
    String TASK_VALUE[6] = {"NOP","SLEEP","LED","REBOOT","FWUPDATE","CNFGUPDATE"};
    TASK type;
    String data;
    int value;
    String ToString(TASK);
    static Task *Instance()
    {
          if (!s_instance)
            s_instance = new Task;
          return s_instance;
    }

};
#endif
