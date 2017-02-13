var express = require('express');
var Menu = require(global.appRoot + '/data/models/v1/menu');
var Category = require(global.appRoot + '/data/models/v1/category');
var MenuMaster = require(global.appRoot + '/data/models/v1/menuMaster');
var Portion = require(global.appRoot + '/data/models/v1/portion');
var app = module.exports = express();
var path = require('path');
var _ = require('lodash');
var uuid = require('node-uuid');
var fs = require('fs');
var multer = require('multer');
var MENU_IMAGES_DIRECTORY = './public/images/menuitems';
var storage = multer.diskStorage({ //multers disk storage settings
    destination: function (req, file, cb) {
        cb(null, MENU_IMAGES_DIRECTORY);
    },
    filename: function (req, file, cb) {
        cb(null, uuid.v4() + path.extname(file.originalname));
    }
});

var upload = multer({ //multer settings
                  storage: storage
              }).single('file');;

/** API path that will upload the files */
app.post('/image', function(req, res, next) {
    upload(req,res,function(err){
        if(err){
              res.json({error_code:1,err_desc:err});
              return;
        }
        res.send(req.file.filename);
    });
});


/* GET home page. */
app.get('/status', function(req, res, next) {
  res.json({
        status: "OK"
              });

});

/* GET All the Menus. */
app.get('/webmenu', function(req, res, next) {

var retValue = [];

    Menu.find(function(err,menus){
      menus.forEach(function(menu) {
        retValue.push(menu.category);
      }, this);
      res.json(retValue);
    });

});


/* GET All the Menus. */
app.get('/', function(req, res, next) {

  
  Portion.find(function(err,portions){
    Menu.find(function(err,menus){
      menus.forEach(function(menu) {
        if(menu.portion.length<1)
          menu.portion=portions;
      }, this);
      res.json(menus);
    });
  });

});

// find and return the menu where the Id matches with the first parameter
app.get('/:id',function(req,res,next){

    var id = req.params.id;

 Portion.find(function(err,portions){
  Menu.findById({_id:req.params.id}, function(err,menu){
    if(menu && menu.portion.length<1)
      menu.portion=portions;
    res.json(
      {
        menu
      });  
    });
  });

});


// update an existing menu 
app.put('/:id',function(req,res,next){

  var status = "error";
  
  Menu.findById({_id:req.params.id}, function(err,menu){
  menu.menuName = req.body.menuName;
  menu.category = req.body.category;
  menu.itemName = req.body.itemName;
  menu.itemDescription = req.body.itemDescription;
  menu.portion = req.body.portion;
  
  //Update or add the category into the category master
  
  var menuMaster = new MenuMaster();
  menuMaster.menuName = menu.menuName;

  var qry = {'menuName':menu.menuName};
  MenuMaster.findOneAndUpdate(qry, menuMaster, {upsert:true}, function(err, doc){
      if (err) 
        status=err;
      else
        status='ok';
  });
  
  //Update or Add the category into the category master
  menu.category.forEach(function(catitem) {
    var cat = new Category();
    var query = {'categoryName':catitem.categoryName};
    Category.findOneAndUpdate(query, catitem, {upsert:true}, function(err, doc){
      if (err) 
        status=err;
      else
        status='ok';
    });
  }, this);


  // if(menu.imageFilename && req.body.imageFilename.length>0)
  // {
  //   if(fs.existsSync(path.join(__dirname,'../../../../',MENU_IMAGES_DIRECTORY,req.body.imageFilename))){
  //     var fileToDelete = path.join(__dirname,'../../../../',MENU_IMAGES_DIRECTORY,menu.imageFilename);
  //     fs.unlink(fileToDelete,function(err){
  //           if(err) 
  //             status='error_file_delete';
  //           else
  //             status="ok";
  //     });  
  //   };
  // }

  menu.imageFilename = req.body.imageFilename;
  
    menu.save(function(err){
      if(!err)
        status = "ok";
      else
        status = err;
      res.json({'status': status});
    }); 
  });
});

// add a new menu 
app.post('/',function(req,res,next){
  
  
  var status = "error";
  var menu = new Menu();
  menu.menuName = req.body.menuName;
  menu.category = req.body.category;
  menu.itemName = req.body.itemName;
  menu.itemDescription = req.body.itemDescription;
  menu.portion = req.body.portion;
  menu.imageFilename = req.body.imageFilename;
  
  //Add the menu name into the Menu Master
  var menuMaster = new MenuMaster();
  menuMaster.menuName = menu.menuName;
  var qry = {'menuName':menu.menuName};
  MenuMaster.findOneAndUpdate(qry, menuMaster, {upsert:true}, function(err, doc){
      if (err) 
        status=err;
      else
        status='ok';
  });
  
  //Add the category into the category master
  menu.category.forEach(function(catitem) {
    var cat = new Category();
    var query = {'categoryName':catitem.categoryName};
    Category.findOneAndUpdate(query, catitem, {upsert:true}, function(err, doc){
      if (err) 
        status=err;
      else
        status='ok';
    });
  }, this);
 

  menu.save(function(err){
    if(!err)
      status = "ok";
    else
      status = err;
  });  
  
  res.json({'status': status});
});



// delete an existing menu
app.delete('/:id',function(req,res,next){

  var status = "menu does not exists";

  console.log(req.params.id);

  Menu.findById({_id:req.params.id},function(err,menu){

    if(err)
      status = err;

    if(menu && menu.imageFilename)
    {
      var fileToDelete = path.join(__dirname,'../../../../',MENU_IMAGES_DIRECTORY,menu.imageFilename);
      fs.unlink(fileToDelete,function(err){
            if(err) 
              status='error_file_delete';
            else
              status="ok";
      });  
    }

    menu.remove(function(err){
      if(err)
        status = 'error';
      else
        status = 'ok';
    });
    res.json({'status': status});
  });
  
  
    
});



