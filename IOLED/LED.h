#ifndef LED_H
#define LED_H
#include "Logger.h"

class LED {
  static LED *s_instance;
public:
	void PlayPattern(int,String,int);
  static LED *Instance()
  {
      if (!s_instance)
        s_instance = new LED;
      return s_instance;
  }
};
#endif
