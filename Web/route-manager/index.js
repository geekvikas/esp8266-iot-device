var express = require('express');
var app = module.exports = express();


// -- Load the API route application
app.use(require('./api-routes'));

// -- Load the WEB route application
app.use(require('./web-routes'));

