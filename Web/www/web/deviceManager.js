var express = require('express');
var app = module.exports = express();
var deviceManager = require(global.appRoot + '/lib/deviceManager');
var path = require('path');

/* Update all clients to redirect their requests to the API Server instead of web*/
app.get('/update/binary',function(req,res,next){
    res.sendFile(path.join(__dirname,"../../public/fw.bin"));
});


/* Update all clients to redirect their requests to the API Server instead of web*/
app.post('/',function(req,res,next){

    var respJson = {};
    var devInfo = deviceManager.GetDeviceInfo(req);
    console.log(devInfo);
    var fwUrl = 'http://10.0.0.221:3000/fw.bin';
    var newConfig = {AP_NAME:"Eshanya",AP_KEY:"eshanyaverma",EP_URL:"http://172.20.10.4:3000/api/v1/device"};
    var newConfigString = JSON.stringify(newConfig);
    
    if(devInfo.firmwareInfo.timestamp != '201702130200')
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.FW_UPDATE,fwUrl,0);
    else
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.CONFIG_UPDATE,newConfigString,0);

    console.log(respJson);
    res.json(respJson);
});
