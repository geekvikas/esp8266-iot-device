var express = require('express');
var Category = require(global.appRoot + '/data/models/v1/category');
var app = module.exports = express();

/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK"
              });

});



/* GET All the Category. */
app.get('/', function(req, res, next) {
  Category.find(function(err,category){
      res.json(category);
  });
});

// find and return the category where the Id matches with the first parameter
app.get('/:id',function(req,res,next){

    var id = req.params.id;

  Category.findById({_id:req.params.id}, function(err,category){
    res.json(
      {
        category
      });  
    });
});


// update an existing category 
app.put('/:id',function(req,res,next){

  var status = "error";

  Category.findById({_id:req.params.id}, function(err,category){
    category.categoryName = req.body.categoryName;
    category.categoryDescription = req.body.categoryDescription;
    category.isTag = req.body.isTag;
    
    category.save(function(err){
      if(!err)
        status = "ok";
      else
        status = err;
      res.json({'status': status});
    }); 
  });
});

// add a new category 
app.post('/',function(req,res,next){
  
  
  var status = "error";
  var category = new Category();
    category.categoryName = req.body.categoryName;
    category.categoryDescription = req.body.categoryDescription;
    category.isTag = req.body.isTag;
    category.save(function(err){
    if(!err)
      status = "ok";
    else
      status = err;
    res.json({'status': status});
  });  
  
    
});


// delete an existing category
app.delete('/:id',function(req,res,next){

  var status = "category does not exists";


  Category.findByIdAndRemove({_id:req.params.id},function(err,category){

    if(err)
      status = err;

    if(category)
      status="ok";
    
    res.json({'status': status});
  });
  
  
    
});



