var express = require('express');
var app = module.exports = express();


// -- Load the Menu API route
var wwwAPI = require('../www/api');
app.use(wwwAPI);
