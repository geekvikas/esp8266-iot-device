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
      console.log(req.body);
      respJson = {status:"success",message: {type:"NOP",data:"",value:0}};
    break;

    case "REG":
      console.log("Registration received...");
      console.log("Old Device Id: " + req.body.message.data);
      respJson = {status:"success",message: {type:"REG_OK",data:"NewDevId",value:0}};
    break;
  }
  res.json(respJson);
});

module.exports = router;
