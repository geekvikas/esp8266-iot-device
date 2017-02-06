#ifndef SYSUTILS_H
#define SYSUTILS_H
#include "Logger.h"

class SysUtils {
private:
	static SysUtils *s_instance;
public:
	void Sleep(unsigned int);
	void Restart();
	void Shutdown();
	static SysUtils *Instance()
    {
          if (!s_instance)
            s_instance = new SysUtils;
          return s_instance;
    }
};

#endif
