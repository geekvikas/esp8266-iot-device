/*
*/


#include "LEDController.h"
const int MIN_LED_INTERVAL      = 100;      // 100 Milliseconds
const int MAX_LED_INTERVAL      = 60000;    // 60 Seconds
const int DEFAULT_LED_INTERVAL  = 2000;     // 2 Seconds

void LEDController::PlayPattern(int PIN, String Pattern, int interval)
{
    if(interval<MIN_LED_INTERVAL || interval>MAX_LED_INTERVAL)
        interval = DEFAULT_LED_INTERVAL;
        
    pinMode(PIN, OUTPUT); 
    byte bytes[Pattern.length()];
    Pattern.getBytes(bytes, Pattern.length());

    int i = 0;
    for (int i = 0; i < Pattern.length(); i++){
        if(bytes[i]=='0')
            digitalWrite(PIN, HIGH);    // Turn OFF the LED
        else
            digitalWrite(PIN, LOW);     // Turn ON the LED

        delay(interval);            // Sleep for a predefined interval
    }
}
