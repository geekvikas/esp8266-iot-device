var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/* GET home page. */
router.post('/', function(req, res, next) {
  var respJson = {};

  switch(req.body.message.type){
    case "HBT":
      console.log("Heartbeat received...");
      //  console.log(req.body);
      var newConfig = {AP_NAME:"Eshanya",AP_KEY:"eshanyaverma",EP_URL:"http://10.0.0.221:3000/"};
      var jString = JSON.stringify(newConfig);
      
      respJson = {status:"success",message: {type:"SLEEP",data: jString,value:0}};
      //console.log(respJson);
    break;

    case "REG":
      console.log("Registration received...");
      console.log("Old Device Id: " + req.body.message.data);
      respJson = {status:"success",message: {type:"REG_OK",data:"NewDevId",value:0}};
    break;
  }
  console.log(JSON.stringify(respJson));
  res.json(respJson);
});

module.exports = router;
