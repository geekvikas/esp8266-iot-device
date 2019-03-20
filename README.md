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
1. Look for "device.json" and connect to WiFi
2. If no "device.json" is present then boot up and try to connect to default WiFi  (Phone based WiFi Hotspot) - credentials: "$DEVICE_DISCOVERY$" "admin@12345"
3. Go to https://whoami.idnno.com/ to download "device.json"
4. device.json contains following information
```
{
	"fingerprint": "KADSHJSJHSJDHSJDBKJSDSKD==",
	"epochUtc": "1352716800",
	"wifiConfig": [
		{
			"ssid": "ssid_1",
			"password": "password_1"
		},
		{
			"ssid": "ssid_2",
			"password": "password_2"
		},
		{
			"ssid": "ssid_3",
			"password": "password_3"
		},
		{
			"ssid": "ssid_4",
			"password": "password_4"
		},
		{
			"ssid": "ssid_5",
			"password": "password_5"
		}
	],
	"commands": {
		"heartbeat": {
			"url": "https://dev.idnno.com/heartbeat",
			"interval": 10000
		},
		"lightStatus": {
			"url": "https://dev.idnno.com/getLightStatus",
			"interval": 10000
		},
		"firmwareCheck": {
			"url": "https://fw.idnno.com/checkUpdate",
			"interval": 14400
		},
		"firmwareUpdate": {
			"url": "https://fw.idnno.com/getUpdate",
			"interval": 0
		}
	}
  ```

5. Connect to WiFi from the Config file
6. Update the device Time from the epochUtc
7. Send a heartbeat and update the status of device in Dashboard
8. Check for FW Update
9. If required, update the FW and reboot, go to Step 1 again
10. Call the lightStatus and change the light accordingly, sleep for the interval in heartbeat
11. go to Step 6
