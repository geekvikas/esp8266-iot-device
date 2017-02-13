var express = require('express');
var app = module.exports = express();

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK"
              });

});


