

#define DEBUG Serial
#define SLEEP_INTERVAL 5
const String CURRENT_VERSION = "0.16";
const String CURRENT_VERSION_FLAVOR = "BETA";
const String CURRENT_VERSION_TIMESTAMP = "201701051200";
const String CURRENT_VERSION_COMMENTS = "Added the device details";
const String BINARY_URL = "http://dev.idnno.com:3000/update/binary";
const String DATA_URL = "http://dev.idnno.com:3000/update/data";
const String HEARTBEAT_URL = "http://dev.idnno.com:3000/heartbeat";
unsigned long baseNTPTime = 0;
unsigned long lastSecs = 0;
unsigned long lastUpdateChecked = 0;
int BootUp = 1;

const int UPDATE_CHECK_THRESHOLD = 1 * 60; // 5 Minutes
ESP8266WiFiMulti WiFiMulti;
String versionData = "{\"version\": \"" + CURRENT_VERSION + "\" , \"flavor\": \"" + CURRENT_VERSION_FLAVOR + "\" , \"timestamp\": \"" + CURRENT_VERSION_TIMESTAMP + "\" , \"comments\": \"" + CURRENT_VERSION_COMMENTS + "\", \"deviceInfo\": DEVICE_INFO_PLACEHOLDER}";


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
    if((WiFiMulti.run() == WL_CONNECTED)) {
          
          SyncTime();
          
          if(UpdateCheckRequired())
            CheckForUpdates();
          else if(HeartBeatRequired())
            SendHeartBeat();
                      
    }
}

void HeartBeatRequired()
{
 if(!FirstRun) // In case of first run, force the update check
            lastUpdateChecked = baseNTPTime - UPDATE_CHECK_THRESHOLD * 2;
  
}


void CheckForUpdates()
{

    if(lastUpdateChecked + UPDATE_CHECK_THRESHOLD <= baseNTPTime && baseNTPTime>0) {
      lastUpdateChecked = baseNTPTime;
      DEBUG.println("Checking for updates...");
      String tmpData = versionData;
      tmpData.replace("DEVICE_INFO_PLACEHOLDER",GetDeviceInfo());
      noError(ESPhttpUpdate.update(BINARY_URL, tmpData));
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


void SyncTime()
{
    unsigned long currentSecs = 0;

    if(BootUp) // First Run, call the NTP Server for time
    {
      DEBUG.println("----------------------Calling NTP Server------------------------");
      baseNTPTime = NTPTime.SecsSince1900();
      BootUp = 0;
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


String GetDeviceInfo()
{
  String retVal = "";
  //return retVal;
         retVal = retVal + "{";
         retVal = retVal +    "\"vcc\":\"" + ESP.getVcc() + "\",";
         retVal = retVal +    "\"freeHeap\":\"" + ESP.getFreeHeap() + "\",";
         retVal = retVal +    "\"bootMode\":\"" + ESP.getBootMode() + "\",";
         retVal = retVal +    "\"cpuFreq\":\"" + ESP.getCpuFreqMHz() + "\",";
         retVal = retVal +    "\"chipId\":\"" + ESP.getChipId() + "\",";
         
         retVal = retVal +    "\"sdkVersion\":\"" + ESP.getSdkVersion() + "\",";
         retVal = retVal +    "\"coreVersion\":\"" + ESP.getCoreVersion() + "\",";
         retVal = retVal +    "\"bootVersion\":\"" + ESP.getBootVersion() + "\",";

         retVal = retVal +    "\"flashChipId\":\"" + ESP.getFlashChipId() + "\",";
         retVal = retVal +    "\"flashChipRealSize\":\"" + ESP.getFlashChipRealSize() + "\",";
         retVal = retVal +    "\"flashChipSize\":\"" + ESP.getFlashChipSize() + "\",";
         retVal = retVal +    "\"flashChipSpeed\":\"" + ESP.getFlashChipSpeed() + "\",";
         retVal = retVal +    "\"flashChipMode\":\"" + ESP.getFlashChipMode() + "\",";
         retVal = retVal +    "\"flashChipSizeByChipId\":\"" + ESP.getFlashChipSizeByChipId() + "\",";
         
         retVal = retVal +    "\"sketchSize\":\"" + ESP.getSketchSize() + "\",";
         retVal = retVal +    "\"sketchMD5\":\"" + ESP.getSketchMD5() + "\",";

         retVal = retVal +    "\"resetReason\":\"" + ESP.getResetReason() + "\",";
         retVal = retVal +    "\"resetInfo\":\"" + ESP.getResetInfo() + "\"";

         retVal = retVal + "}";

  return retVal;
}


