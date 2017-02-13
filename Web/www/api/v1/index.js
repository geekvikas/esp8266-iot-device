var express = require('express');
var app = module.exports = express();

var menu = require('./menu');
var menuMaster = require('./menu/menuMaster');
var category = require('./category');
var portion = require('./portion');

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK",
        serviceVersion: 'v1'
              });

});


app.use('/menu', menu);
app.use('/menuMaster', menuMaster);
app.use('/category', category);
app.use('/portion', portion);
