var express = require('express');
var app = module.exports = express();


/* load up Menu Manager */
app.get('/', function(req, res, next) {
  res.render('homePage');
});

/* load up Menu Manager */
app.get('/admin/menu/', function(req, res, next) {
  res.render('menuMaker',{title:"Menu Maker"});
});


/* load up Category Manager */
app.get('/admin/master/category/', function(req, res, next) {
  res.render('categoryMaster',{title:"Category Manager"});
});


/* load up Menu Master */
app.get('/admin/master/menu/', function(req, res, next) {
  res.render('menuMaster',{title:"Menu Manager"});
});


/* load up Portion Manager */
app.get('/admin/master/portion/', function(req, res, next) {
  res.render('portionMaster',{title:"Portion Manager"});
});


/* load up Menu Manager */
app.get('/test', function(req, res, next) {
  res.render('tester',{title:"Test Title"});
});
