#include "Http.h"
#include <ESP8266HTTPClient.h>




String Http::Get(String url){
	String retVal;
	__http.begin(url);
    int httpCode = __http.GET();
    if(httpCode == HTTP_CODE_OK)
        retVal = __http.getString();
    __http.end();
		return retVal;
}

String Http::Post(String url,String body){
	String retVal;
	__http.begin(url);
    int httpCode = __http.POST(body);
    if(httpCode == HTTP_CODE_OK)
        retVal = __http.getString();
    __http.end();
		return retVal;
}