# IO LED
A simple Single LED based device that display different pattern of LED depending upon the command received from central server

# Directory Structure

## Firmware
Contains the entire Arduino Project. `Firmware.ino` is the main file.

### Compiling the code from VS Code
I have used https://github.com/fabienroyer/VisualStudioCodeArduino to help me compile / upload the sketch directly from VSCode.
You can compile it manually and update using Arduino IDE as well.


## Web
This is the source code for NodeJs / MEAN app for managing / viewing the registered devices. Web server manage the registration and can be used to send commands to each device as response to heartbeat event. This allow for completely disconnected and one way traffic, also known as "Push initiated by Pull"

Current supported `Tasks` are 

```
enum TASK{
      NOP,            // No operation is required
      REG_OK,         // Valid Registration received from server, update the local device Id and registration check skip limit
      REG_INVALID,    // Invalid Registration - Potentially forced re-registration check from server, device lost mode
      SLEEP,          // Sleep the device for a certain period, save battery
      LED,            // LED operation
      CONFIG_UPDATE,  // Update the local Configuration file from a Server URL
      FACTORY_RESET,  // Remove the local config file and revert back to Default configurations, drop the Network connections
      FW_UPDATE,      // Update the local FW from a Server URL
      REBOOT,         // Reboot the device
      SHUTDOWN        // Turn Off / Shutdown the device. Forced re-registration by server, or device BLACKLIST mode
    };
 ```


# Boot Process
1. Look for *default.config* and connect to WiFi
2. If no *default.config* is present then boot up and try to connect to default WiFi 
	* SSID : `$DEVICE_DISCOVERY$`
	* Pass : `admin@12345`
3. Go to *http://dev.idnno.com/api/v1/device* to download *default.config*
4. *default.config* contains following information
```
{
	"AP_NAME":"SSID_HERE",
	"AP_KEY":"Super_Secret_Password_Here",
	"EP_URL":"http://XXX.YYY.ZZZ.AAA:3000/"
}
```

5. Connect to WiFi from the Config file
6. Update the device Time from the epochUtc
7. Send a heartbeat and update the status of device in Dashboard
8. Check for FW Update
9. If required, update the FW and reboot, go to Step 1 again
10. Call the lightStatus and change the light accordingly, sleep for the interval in heartbeat
11. go to Step 6
