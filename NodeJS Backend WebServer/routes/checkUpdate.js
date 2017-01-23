var express = require('express');
var router = express.Router();
var path = require('path');
var LATEST_VERSION = 0.16;

/* GET users listing. */
// router.get('/data', function(req, res, next) {
//   console.log(JSON.stringify(req.headers));
//   res.status(200);
//   res.sendFile(path.join(__dirname, '../fwupdate', 'data.bin'));
// });

router.get('/binary', function(req, res, next) {

  var json_version = null;
  try{
    //console.log(req.header("x-esp8266-version"));
    json_version = JSON.parse(req.header("x-esp8266-version"));
    // console.log("Current Version: " + json_version.version + 
    //             " , Flavor: " + json_version.flavor + 
    //             " , TimeStamp: " + json_version.timestamp + 
    //             " , Comments: " + json_version.comments + 
    //             " , DeviceInfo - VCC: " + json_version.deviceInfo.vcc);

    console.log(json_version);

    if(json_version.version && json_version.version<LATEST_VERSION){
        res.status(200).sendFile(path.join(__dirname, '../fwupdate', 'fw.bin'));
    }
    else
      res.status(304).json({error: "No Update Required"});
  }
  catch(e){
        res.status(400).json({error: "Invalid Request"});
        res.end();
  }
  //console.log(json_version);

  // if(!json_version){
  //       res.status(400).json({error: "Invalid Request"});
  //       res.end();
  // }
  // else if(json_version.version>1){
  //     res.status(200).sendFile(path.join(__dirname, '../fwupdate', 'fw.bin'));
  // }
  // else
  //   res.status(304).json({error: "No Update Required"});
  });

  
module.exports = router;
