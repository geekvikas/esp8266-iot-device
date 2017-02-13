var express = require('express');
var app = module.exports = express();


// -- Load the wwwroot route
var wwwroot = require('../www/web');
app.use(wwwroot);



