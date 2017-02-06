#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H
#include "Logger.h"

class LEDController {
  static LEDController *s_instance;
public:
	void PlayPattern(int,String,int);
  static LEDController *Instance()
  {
      if (!s_instance)
        s_instance = new LEDController;
      return s_instance;
  }
};
#endif
