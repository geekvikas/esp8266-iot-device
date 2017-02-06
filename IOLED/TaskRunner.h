#ifndef TASKRUNNER_H
#define TASKRUNNER_H
#include "Task.h"
#include "Device.h"
#include "LEDController.h"
#include "Logger.h"

class TaskRunner {
private:
	static TaskRunner *s_instance;
public:
	void Run(Task);
	static TaskRunner *Instance()
    {
          if (!s_instance)
            s_instance = new TaskRunner;
          return s_instance;
    }
};
#endif
