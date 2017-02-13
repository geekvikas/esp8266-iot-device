var Device = require(global.appRoot + '/data/models/v1/device');
    
var TASK = exports.TASK = {
      NOP : 'NOP',                      // No operation is required
      REG_OK : 'REG_OK',                // Valid Registration received from server, update the local device Id and registration check skip limit
      REG_INVALID : 'REG_INVALID',      // Invalid Registration - Potentially forced re-registration check from server, device lost mode
      SLEEP : 'SLEEP',                  // Sleep the device for a certain period, save battery
      LED : 'LED',                      // LED operation
      CONFIG_UPDATE : 'CONFIG_UPDATE',  // Update the local Configuration file from a Server URL
      FACTORY_RESET : 'FACTORY_RESET',  // Remove the local config file and revert back to Default configurations, drop the Network connections
      FW_UPDATE : 'FW_UPDATE',          // Update the local FW from a Server URL
      REBOOT : 'REBOOT',                // Reboot the device
      SHUTDOWN : 'SHUTDOWN'             // Turn Off / Shutdown the device. Forced re-registration by server, or device BLACKLIST mode
};

var REQUEST_TYPE = exports.REQUEST_TYPE = {
      REGISTRATION : 'REG',             // Registration request received from client, client may not have a valid device Id
      HEART_BEAT : 'HBT'                // A times HEART_BEAT received from client, the response should have any pending tasks
};
var GetDeviceInfo = exports.GetDeviceInfo = function(req){
    var devInfo;
    var userAgent = req.header('user-agent');
      
    // If the request came from IOLED device
    if(!(userAgent && userAgent.indexOf('IOLED') == 0))
    {
      return;
    }

    var header = req.header('x-ESP8266-version');
    
    if(header)
      devInfo = JSON.parse(header);
    else
      devInfo = req.body;
    
    return devInfo;

};

var GenerateMessage = exports.GenerateMessage= function(status,type,data,value){
    if(!status)
        status = "success";
        
    if(!type)
        type = REQUEST_TYPE.NOP;
        
    if(!data)
        data = "";
        
    if(!value)
        value = 0;

    return {status:status,message: {type:type,data: data,value:value}};
};
