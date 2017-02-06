#ifndef HTTP_H
#define HTTP_H
#include <ESP8266HTTPClient.h>

class Http {
private:
  HTTPClient __http;
  static Http *s_instance;
 

public:
  
	String Get(String);
 	String Post(String,String);
	static Http *Instance()
    {
        if (!s_instance)
          s_instance = new Http;
        return s_instance;
    }
};

#endif
