var express = require('express');
var Portion = require(global.appRoot + '/data/models/v1/portion');
var app = module.exports = express();

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK"
              });

});



/* GET All the Portion. */
app.get('/', function(req, res, next) {
  Portion.find(function(err,portion){
      res.json(portion);
  });
});

// find and return the portion where the Id matches with the first parameter
app.get('/:id',function(req,res,next){

    var id = req.params.id;

  Portion.findById({_id:req.params.id}, function(err,portion){
    res.json(
      {
        portion
      });  
    });
});


// update an existing portion 
app.put('/:id',function(req,res,next){

  var status = "error";

  Portion.findById({_id:req.params.id}, function(err,portion){
    portion.portionName = req.body.portionName;
    portion.portionDescription = req.body.portionDescription;
    portion.isTag = req.body.isTag;
    
    portion.save(function(err){
      if(!err)
        status = "ok";
      else
        status = err;
      res.json({'status': status});
    }); 
  });
});

// add a new portion 
app.post('/',function(req,res,next){
  
  
  var status = "error";
  var portion = new Portion();
    portion.portionName = req.body.portionName;
    portion.portionDescription = req.body.portionDescription;
    portion.isTag = req.body.isTag;
    portion.save(function(err){
    if(!err)
      status = "ok";
    else
      status = err;
    res.json({'status': status});
  });  
  
    
});


// delete an existing portion
app.delete('/:id',function(req,res,next){

  var status = "portion does not exists";


  Portion.findByIdAndRemove({_id:req.params.id},function(err,portion){

    if(err)
      status = err;

    if(portion)
      status="ok";
    
    res.json({'status': status});
  });
  
  
    
});



