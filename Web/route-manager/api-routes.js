var express = require('express');
var app = module.exports = express();


// -- Load the Menu API route
var menu_api = require('../www/api');
app.use(menu_api);
