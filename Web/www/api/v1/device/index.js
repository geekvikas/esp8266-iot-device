var express = require('express');
var Device = require(global.appRoot + '/data/models/v1/device');
var app = module.exports = express();

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK"
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


// update an existing device 
app.put('/:id',function(req,res,next){

  var status = "error";

  Device.findById({_id:req.params.id}, function(err,device){
    device.name = req.body.name;
    device.description = req.body.description;
    
    device.save(function(err){
      if(!err)
        status = "ok";
      else
        status = err;
      res.json({'status': status});
    }); 
  });
});

// add a new Device 
app.post('/',function(req,res,next){
  
  
  var status = "error";
  var device = new Device();
    device.name = req.body.name;
    device.description = req.body.description;
    device.save(function(err){
    if(!err)
      status = "ok";
    else
      status = err;
    res.json({'status': status});
  });  
  
    
});


// delete an existing Device
app.delete('/:id',function(req,res,next){

  var status = "Device does not exists";


  Device.findByIdAndRemove({_id:req.params.id},function(err,device){

    if(err)
      status = err;

    if(device)
      status="ok";
    
    res.json({'status': status});
  });
  
  
    
});



