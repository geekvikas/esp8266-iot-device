 /**
 * httpUpdateSPIFFS.ino
 *
 *  Created on: 05.12.2015
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

#include "NTPTime.h"

#define DEBUG Serial
#define SLEEP_INTERVAL 5
const String CURRENT_VERSION = "0.15";
const String CURRENT_VERSION_FLAVOR = "BETA";
const String CURRENT_VERSION_TIMESTAMP = "201612310545";
const String CURRENT_VERSION_COMMENTS = "New Time Check Method";
const String BINARY_URL = "http://dev.idnno.com:3000/update/binary";
const String DATA_URL = "http://dev.idnno.com:3000/update/data";
unsigned long baseNTPTime = 0;
unsigned long lastSecs = 0;
unsigned long lastUpdateChecked = 0;
const int UPDATE_CHECK_THRESHOLD = 1 * 60; // 5 Minutes
ESP8266WiFiMulti WiFiMulti;
String versionData = "{\"version\": \"" + CURRENT_VERSION + "\" , \"flavor\": \"" + CURRENT_VERSION_FLAVOR + "\" , \"timestamp\": \"" + CURRENT_VERSION_TIMESTAMP + "\" , \"comments\": \"" + CURRENT_VERSION_COMMENTS + "\"}";


void setup() {
    
    DEBUG.begin(115200);
    // DEBUG.setDebugOutput(true);

    DEBUG.printf("Current Version: %s ( %s )\n" , CURRENT_VERSION.c_str() ,CURRENT_VERSION_FLAVOR.c_str());
    
    for(uint8_t t = 4; t > 0; t--) {
        DEBUG.printf("[SETUP] WAIT %d...\n", t);
        DEBUG.flush();
        delay(1000);
    }


    WiFiMulti.addAP("Eshanya", "eshanyaverma");

}

void loop() {


    
    DEBUG.printf("Current Version: %s ( %s )\n" , CURRENT_VERSION.c_str() ,CURRENT_VERSION_FLAVOR.c_str());
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {

          
          SyncTime();

          
          if(lastUpdateChecked<=0) // In case of first run, force the update check
            lastUpdateChecked = baseNTPTime - UPDATE_CHECK_THRESHOLD * 2;
          
          if(lastUpdateChecked + UPDATE_CHECK_THRESHOLD <= baseNTPTime) {
           lastUpdateChecked = baseNTPTime;
           DEBUG.println("Checking for updates...");
           noError(ESPhttpUpdate.update(BINARY_URL, versionData));
          }
    }
}


boolean noError(t_httpUpdate_return ret)
{
    boolean retVal = false;
      switch(ret) {
                case HTTP_UPDATE_FAILED:
                    DEBUG.printf("HTTP_UPDATE_FAILD Error (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                    break;

                case HTTP_UPDATE_NO_UPDATES:
                    DEBUG.println("HTTP_UPDATE_NO_UPDATES");
                    break;

                case HTTP_UPDATE_OK:
                    DEBUG.println("HTTP_UPDATE_OK");
                    retVal = true;
                    break;
            }
    return retVal;
}



void getSeconds()

{
  //Written by Ruben Marc Speybrouck

unsigned long timeNow = 0;

unsigned long timeLast = 0;

//Time start Settings:

int startingHour = 12;

// set your starting hour here, not below at int hour. This ensures accurate daily correction of time

int seconds = 0;

int minutes = 33;

int hours = startingHour;

int days = 0;

//Accuracy settings

int dailyErrorFast = 0; // set the average number of milliseconds your microcontroller's time is fast on a daily basis

int dailyErrorBehind = 0; // set the average number of milliseconds your microcontroller's time is behind on a daily basis

int correctedToday = 1; // do not change this variable, one means that the time has already been corrected today for the error in your boards crystal. This is true for the first day because you just set the time when you uploaded the sketch.


timeNow = millis()/1000; // the number of milliseconds that have passed since boot

seconds = timeNow - timeLast;

//the number of seconds that have passed since the last time 60 seconds was reached.

if (seconds == 60) {

timeLast = timeNow;

minutes = minutes + 1; }

//if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.

if (minutes == 60){

minutes = 0;

hours = hours + 1; }



// if one hour has passed, start counting minutes from zero and add one hour to the clock



if (hours == 24){

hours = 0;

days = days + 1;

}

//if 24 hours have passed, add one day

if (hours ==(24 - startingHour) && correctedToday == 0){

delay(dailyErrorFast*1000);

seconds = seconds + dailyErrorBehind;

correctedToday = 1; }

//every time 24 hours have passed since the initial starting time and it has not been reset this day before, add milliseconds or delay the program with some milliseconds.

//Change these varialbes according to the error of your board.

// The only way to find out how far off your boards internal clock is, is by uploading this sketch at exactly the same time as the real time, letting it run for a few days

// and then determining how many seconds slow/fast your boards internal clock is on a daily average. (24 hours).

if (hours == 24 - startingHour + 2) {

correctedToday = 0; }

//let the sketch know that a new day has started for what concerns correction, if this line was not here the arduiono // would continue to correct for an entire hour that is 24 - startingHour.

DEBUG.print("The time is: ");

DEBUG.print(days);

DEBUG.print(":");

DEBUG.print(hours);

DEBUG.print(":");

DEBUG.print(minutes);

DEBUG.print(":");

DEBUG.println(seconds);
}


void SyncTime()
{
    unsigned long currentSecs = 0;

    if(baseNTPTime == 0) // First Run
    {
      DEBUG.println("----------------------Calling NTP Server------------------------");
      baseNTPTime = NTPTime.SecsSince1900();
    }

    currentSecs = millis()/1000;
    
    if(currentSecs>lastSecs+5)
    {
      baseNTPTime = baseNTPTime + (currentSecs-lastSecs);
      lastSecs = currentSecs;
    
      // now convert NTP time into everyday time:
      DEBUG.print("Unix time = ");
      // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
      const unsigned long seventyYears = 2208988800UL;
      // subtract seventy years:
      unsigned long epoch = baseNTPTime - seventyYears;
      // print Unix time:
      DEBUG.println(epoch);
  
  
      // print the hour, minute and second:
      DEBUG.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
      DEBUG.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
      DEBUG.print(':');
      if ( ((epoch % 3600) / 60) < 10 ) {
        // In the first 10 minutes of each hour, we'll want a leading '0'
        DEBUG.print('0');
      }
      DEBUG.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
      DEBUG.print(':');
      if ( (epoch % 60) < 10 ) {
        // In the first 10 seconds of each minute, we'll want a leading '0'
        DEBUG.print('0');
      }
      DEBUG.println(epoch % 60); // print the second
    }
}

