var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

/* GET home page. */
router.post('/', function(req, res, next) {
  console.log(req);
  res.json({status:"success",message: {type:"LED",data:"1010101010101010101010",value:100}});
});

module.exports = router;
