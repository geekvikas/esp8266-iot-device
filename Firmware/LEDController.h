#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

 #define LED_OFF HIGH
#define LED_ON  LOW

#include "SysUtils.h"
#include "Logger.h"


class LEDController {
  private:

    static LEDController *s_instance;

  public:

    

    void PlayPattern(int,String,int);

    void PlayPattern(int,String,int,int);

    static LEDController *Instance()
    {
        if (!s_instance)
          s_instance = new LEDController;
        return s_instance;
    }

};
#endif
