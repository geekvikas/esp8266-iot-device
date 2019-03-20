var express = require('express');
var Device = require(global.appRoot + '/data/models/v1/device');
var deviceManager = require(global.appRoot + '/lib/deviceManager');

var app = module.exports = express();

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "success"
              });

});



/* GET All the Device */
app.get('/', function(req, res, next) {
  Device.find(function(err,device){
      res.json(device);
  });
});

// find and return the devices where the Id matches with the first parameter
app.get('/:id',function(req,res,next){

  var id = req.params.id;

  Device.findById({_id:req.params.id}, function(err,device){
    res.json(
      {
        device
      });  
    });
});

// find and return the devices where the Id matches with the first parameter
app.get('/chipid/:id',function(req,res,next){

  var id = req.params.id;
 
  Device.find({'deviceInfo.chipId':id}, function(err,device){
      if(!err){
        res.json(
          {
            device
          });  
      }
      else
        {
          res.jsonp(err);
        }

    });
});


// update an existing device 
app.put('/:id',function(req,res,next){

  var status = "error";

  Device.findById({_id:req.params.id}, function(err,device){
    device = new Device(req.body);
    
    device.save(function(err){
      if(!err)
        status = "success";
      else
        status = err;
      res.json({'status': status});
    }); 
  });
});

// add a new Device 
app.post('/',function(req,res,next){
  
  
  var respJson = {};
  var devInfo = deviceManager.GetDeviceInfo(req);
  console.log("Request Type: " + devInfo.message.type + ' , Timestamp: ' + devInfo.firmwareInfo.timestamp + ' , FW Version: ' + devInfo.firmwareInfo.version);
  var fwUrl = 'http://dev.idnno.com/fw.bin';
  var newConfig = {AP_Name:"WIFI_SSID",AP_Key:"SSID_PASSWORD",EP_URL:"http://dev.idnno.com/api/v1/device"};
  var newConfigString = JSON.stringify(newConfig);

  var status = "error";
  var device = new Device();
  
  if(devInfo.firmwareInfo.timestamp != '201702160630')
  { 
    respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.FW_UPDATE,fwUrl,0);
    res.json(respJson);
    return;
  }
  


  if(devInfo.message.type == deviceManager.REQUEST_TYPE.REGISTRATION)
  {
    Device.find({'deviceInfo.chipId':devInfo.deviceInfo.chipId}, function(err,device){
      if(!err && Object.keys(device).length==1 && device[0].deviceInfo.chipId == devInfo.deviceInfo.chipId){
        // Device with same chipId found in the system, return the same record back
        console.log('Existing record found for this device: ' + device[0]._id);
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.REG_OK,device[0]._id);    
        res.json(respJson);
      }
      else
      {
        device = new Device(req.body);
        device.save(function(err){
          if(!err){
            // Device is not in the system, so register it 
            console.log('New record created for this device: ' + device._id);
            respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.REG_OK,device._id);    
            res.json(respJson);
          }
          else{
            respJson = deviceManager.GenerateMessage("error",deviceManager.TASK.REG_INVALID);    
            console.log('Error in creating a new record for this device: ' + err);
            res.json(respJson);
          }
        }); 
      }
    });
  }
  else if(devInfo.message.type == deviceManager.REQUEST_TYPE.HEART_BEAT)
  {
    //Check if device is still registered in the database
    Device.find({'deviceInfo.chipId':devInfo.deviceInfo.chipId}, function(err,device){
      if(!err && Object.keys(device).length==1 && device[0].deviceInfo.chipId == devInfo.deviceInfo.chipId){
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.LED,"110110110110",200);
      }
      else{
        // If device is not registered then force re-registration by sending REG_INVALID response
        respJson = deviceManager.GenerateMessage("success",deviceManager.TASK.REG_INVALID);
      }
      res.json(respJson);
    });
   
  }
  else{
    respJson = deviceManager.GenerateMessage("error",deviceManager.TASK.NOP);
    res.json(respJson);
  }

});
  

    


// delete an existing Device
app.delete('/:id',function(req,res,next){

  var status = "Device does not exists";


  Device.findByIdAndRemove({_id:req.params.id},function(err,device){

    if(err)
      status = err;

    if(device)
      status="success";
    
    res.json({'status': status});
  });
  
  
    
});



