var express = require('express');
var app = module.exports = express();

var webTitle = "IOLED";
var webDescription = "IOLED";
var webLogoURL = "";
var fbURL = "http:///";
var gpURL = "http:///";
var igURL = "http:///";

/* load up Dashboard */
app.get('/', function(req, res, next) {
  res.render('dashboard',{
      webTitle:webTitle,
      webDescription:webDescription,
      webLogoURL:webLogoURL,
      fbURL:fbURL,
      gpURL:gpURL,
      igURL:igURL
    });
});
