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
    var fwUrl = 'http://dev.idnno.com/fw.bin';
    var newConfig = {AP_NAME:"Eshanya",AP_KEY:"eshanyaverma",EP_URL:"http://dev.idnno.com/api/v1/device"};
    var newConfigString = JSON.stringify(newConfig);
    
    if(devInfo.firmwareInfo.timestamp != '201702130200')
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.FW_UPDATE,fwUrl,0);
    else
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.CONFIG_UPDATE,newConfigString,0);

    console.log(respJson);
    res.json(respJson);
});
