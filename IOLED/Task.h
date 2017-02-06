#ifndef TASK_H
#define TASK_H
#include "Logger.h"


enum TASK{
      NOP,            // No operation is required
      REG_OK,         // Valid Registration received from server, update the local device Id and registration check skip limit
      REG_INVALID,    // Invalid Registration - Potentially forced re-registration check from server, device lost mode
      SLEEP,          // Sleep the device for a certain period, save battery
      LED,            // LED operation
      CONFIG_UPDATE,  // Update the local Configuration file from a Server URL
      FW_UPDATE,      // Update the local FW from a Server URL
      REBOOT,         // Reboot the device
      SHUTDOWN        // Turn Off / Shutdown the device. Forced re-registration by server, or device BLACKLIST mode
    };

class Task {
  private:
    static Task *s_instance;

  public:
    
    String TASK_VALUE[9] = {
        "NOP",
        "REG_OK",
        "REG_INVALID",
        "SLEEP",
        "LED",
        "CONFIG_UPDATE",
        "FW_UPDATE",
        "REBOOT",
        "SHUTDOWN"
        };
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
