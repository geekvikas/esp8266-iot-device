var express = require('express');
var path = require('path'); global.appRoot = path.resolve(__dirname);
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var routeManager = require('./route-manager');
var app = express();
var dbConnection = require('./data/connection.js')


var mongoDBServer = process.env.MONGO_PORT_27017_TCP_ADDR   || 'localhost';
var mongoDBPort = process.env.MONGO_PORT_27017_TCP_PORT || '27017';
var mongoDBName = process.env.MONGO_DATABASE_NAME || 'ioled';

var mongoDBConnectionString = 'mongodb://' + mongoDBServer + ':' + mongoDBPort + '/' + mongoDBName;


// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');

// uncomment after placing your favicon in /public
//app.use(favicon(path.join(__dirname, 'public', 'favicon.ico')));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));
app.use(routeManager);


// catch 404 and forward to error handler
app.use(function(req, res, next) {
  //res.redirect('/admin/menu/list');
   var err = new Error('Not Found');
   err.status = 404;
   next(err);
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

// Connect to Mongo on start
dbConnection.connect( mongoDBConnectionString , function(err) {
  if (err) {
    console.log('Unable to connect to: ' + mongoDBConnectionString);
    process.exit(1);
  }
  else
    console.log('DB Connected to: ' + mongoDBConnectionString);
});


module.exports = app;
