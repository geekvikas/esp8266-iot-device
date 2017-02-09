var express = require('express');
var router = express.Router();

var TASK  = {
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


/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});


/* GET home page. */
router.get('/fw', function(req, res, next) {
  var header = req.header('x-ESP8266-version');
  if(header){
    var devInfo = JSON.parse(header);
    console.log('Device Version: ' + devInfo.firmwareInfo.version);
  }
  res.sendFile('C:\\dev\\esp8266\\NodeJS Backend WebServer\\10RC.bin');
});

/* GET home page. */
router.post('/', function(req, res, next) {
  var header = req.header('x-ESP8266-version');
  var devInfo;

  if(header)
    devInfo = JSON.parse(header);
  else
    devInfo = req.body;

  console.log('Device Version: ' + devInfo.firmwareInfo.version);


  var respJson = {};

  switch(req.body.message.type){
    case "HBT":
      console.log("Heartbeat received...");
      //  console.log(req.body);
      var newConfig = {AP_NAME:"Eshanya",AP_KEY:"eshanyaverma",EP_URL:"http://10.0.0.221:3000/"};
      var newConfigString = JSON.stringify(newConfig);
      var LED_Pattern = '1.1.1.1.1.1.1.1.1.1.1.1.1.1.';
      var fwUrl = 'http://10.0.0.221:3000/fw';
      respJson = {status:"success",message: {type:TASK.SHUTDOWN,data: LED_Pattern,value:25}};
      //respJson = {status:"success",message: {type:TASK.FW_UPDATE,data: fwUrl,value:25}};
      //console.log(respJson);
    break;

    case "REG":
      console.log("Registration received...");
      console.log("Old Device Id: " + req.body.message.data);
      respJson = {status:"success",message: {type:TASK.REG_OK,data:"device_id_here",value:0}};
    break;
  }
  console.log(JSON.stringify(respJson));
  res.json(respJson);
});

module.exports = router;
