var express = require('express');
var app = module.exports = express();

var device = require('./device');


/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK",
        serviceVersion: 'v1'
              });

});


app.use('/device', device);