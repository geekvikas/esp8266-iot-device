/*
*/


#include "LEDController.h"
const int MIN_LED_INTERVAL      = 25;       // 10 Milliseconds
const int MAX_LED_INTERVAL      = 60000;    // 60 Seconds
const int DEFAULT_LED_INTERVAL  = 2000;     // 2 Seconds
const int MIN_LOOP_COUNT        = 1;       // 1 Loop


void LEDController::PlayPattern(int PIN, String Pattern, int Interval)
{
    return PlayPattern(PIN,Pattern,Interval,MIN_LOOP_COUNT);
}

void LEDController::PlayPattern(int PIN, String Pattern, int Interval, int LoopCount)
{
    if(Interval < MIN_LED_INTERVAL || Interval > MAX_LED_INTERVAL)
        Interval = DEFAULT_LED_INTERVAL;
        
    pinMode(PIN, OUTPUT); 

    int patternIdx = 0, loopIdx;

    for(int loopIdx = 0; loopIdx<LoopCount; loopIdx++){         // Run the pattern for LoopCount times
        for (int patternIdx = 0; patternIdx < Pattern.length(); patternIdx++){
            if(Pattern.charAt(patternIdx) == '1')
                digitalWrite(PIN, LED_ON);    
            else
                digitalWrite(PIN, LED_OFF);     

            SysUtils::Instance()->Sleep(Interval);            // Sleep for a predefined interval
        }
    }
}
