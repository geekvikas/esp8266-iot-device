var express = require('express');
var app = module.exports = express();

var apiV1 = require('./v1');
var apiDefaultVersion = require('./v1');

app.use('/api/v1', apiV1);
app.use('/api/', apiDefaultVersion);


