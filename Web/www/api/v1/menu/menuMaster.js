var express = require('express');
var MenuMaster = require(global.appRoot + '/data/models/v1/menuMaster');
var app = module.exports = express();

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK"
              });

});



/* GET All the MenuMaster. */
app.get('/', function(req, res, next) {
  MenuMaster.find(function(err,menuMaster){
      res.json(menuMaster);
  });
});

// find and return the menuMaster where the Id matches with the first parameter
app.get('/:id',function(req,res,next){

    var id = req.params.id;

  MenuMaster.findById({_id:req.params.id}, function(err,menuMaster){
    res.json(
      {
        menuMaster
      });  
    });
});


// update an existing menuMaster 
app.put('/:id',function(req,res,next){

  var status = "error";

  MenuMaster.findById({_id:req.params.id}, function(err,menuMaster){
    menuMaster.menuName = req.body.menuName;
    menuMaster.menuDescription = req.body.menuDescription;
    menuMaster.isTag = req.body.isTag;
    
    menuMaster.save(function(err){
      if(!err)
        status = "ok";
      else
        status = err;
      res.json({'status': status});
    }); 
  });
});

// add a new menuMaster 
app.post('/',function(req,res,next){
  
  
  var status = "error";
  var menuMaster = new MenuMaster();
    menuMaster.menuName = req.body.menuName;
    menuMaster.menuDescription = req.body.menuDescription;
    menuMaster.isTag = req.body.isTag;
    menuMaster.save(function(err){
    if(!err)
      status = "ok";
    else
      status = err;
    res.json({'status': status});
  });  
  
    
});


// delete an existing menuMaster
app.delete('/:id',function(req,res,next){

  var status = "menuMaster does not exists";


  MenuMaster.findByIdAndRemove({_id:req.params.id},function(err,menuMaster){

    if(err)
      status = err;

    if(menuMaster)
      status="ok";
    
    res.json({'status': status});
  });
  
  
    
});



