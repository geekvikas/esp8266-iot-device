  var app = angular.module('grub.desi.admin', ['ngResource',  'ngAnimate', 'toaster','angular.filter','ngFileUpload','ui.select','ngSanitize']);

 

  /**
   * AngularJS default filter with the following expression:
   * "person in people | filter: {name: $select.search, age: $select.search}"
   * performs an AND between 'name: $select.search' and 'age: $select.search'.
   * We want to perform an OR.
   */
  app.filter('propsFilter', function() {
    return function(items, props) {
      var out = [];

      if (angular.isArray(items)) {
        var keys = Object.keys(props);

        items.forEach(function(item) {
          var itemMatches = false;

          for (var i = 0; i < keys.length; i++) {
            var prop = keys[i];
            var text = props[prop].toLowerCase();
            if (item[prop] && item[prop].toString().toLowerCase().indexOf(text) !== -1) {
              itemMatches = true;
              break;
            }
          }

          if (itemMatches) {
            out.push(item);
          }
        });
      } else {
        // Let the output be the input untouched
        out = items;
      }

      return out;
    };
  });


  app.config(function ($httpProvider) {
    $httpProvider.interceptors.push('myHttpInterceptor');
  });


  // Handle http server errors
  app.factory('myHttpInterceptor', function ($q,toaster) {
      return {
          responseError: function (response) {
            console.log(response);
            if(response.data){
              if(response.data.message)
                  toaster.error('Error: ', response.data.message);
              else
                  toaster.error('Error: ', response.data);
            }
            return $q.reject(response);
          }
      };
  });
  

  // Showing loading indicator on top while data is requested from database
  app.directive('loading',  ['$http',  function ($http)
  { 
      //var progressbar = ngProgressFactory.createInstance();
                    
      return {
          restrict: 'A',
          link: function (scope, elm, attrs)
          {
              scope.isLoading = function () {
                  return $http.pendingRequests.length > 0;
              };

              scope.$watch(scope.isLoading, function (v)
              {
                  if(v){
                      // progressbar.setHeight('3px');
                      // progressbar.setColor('yellow');
                      // progressbar.start();
                  }else{
                      //$('select').selectpicker();
                      // progressbar.complete();
                  }
              });
          }
      };
  }]);
  
  // Create a resource factory to access products table from database 
  app.factory('Menu', function($resource) {
    return $resource('/api/v1/menu/:id', { id: '@_id' }, {
      update: { // We need to define this method manually as it is not provided with ng-resource
        method: 'PUT'
      }
    });
  });

  
  // Create a resource factory to access products table from database 
  app.factory('Category', function($resource) {
    return $resource('/api/v1/category/:id', { id: '@_id' }, {
      update: { // We need to define this method manually as it is not provided with ng-resource
        method: 'PUT'
      }
    });
  });

  
  // Create a resource factory to access products table from database 
  app.factory('Portion', function($resource) {
    return $resource('/api/v1/portion/:id', { id: '@_id' }, {
      update: { // We need to define this method manually as it is not provided with ng-resource
        method: 'PUT'
      }
    });
  });

  
  // Create a resource factory to access products table from database 
  app.factory('MenuMaster', function($resource) {
    return $resource('/api/v1/menuMaster/:id', { id: '@_id' }, {
      update: { // We need to define this method manually as it is not provided with ng-resource
        method: 'PUT'
      }
    });
  });



(function () {
    
    var app = angular.module('grubdesi', ['ngRoute']);
    app.controller('MenuDBController', function ($scope, $http) {
        
        $http.get('/menu.json')
             .then(function (res) {
                 $scope.menus = res.data;
                 $scope.menu_loaded = true;
             });
    });

    app.controller('emailer', function ($scope, $http, $log, $timeout) {
            // Inititate the promise tracker to track form submissions.
            //$scope.progress = promiseTracker();

            // Form submit handler.
            $scope.submit = function(form) {
                // Trigger validation flag.
                $scope.submitted = true;

                // If form is invalid, return and let AngularJS show validation errors.
                if (form.$invalid) {
                    return;
                }
                // Default values for the request.
                var config = {
                    params : {
                    'callback' : 'JSON_CALLBACK',
                    'firstname' : $scope.firstname,
                    'lastname' : $scope.lastname,
                    'email' : $scope.email,
                    'phone' : $scope.phone,
                    'comments' : $scope.comments
                    },
                };

            // Perform JSONP request.
            var $promise = $http.jsonp('/enquiry.json', config)
                .success(function(data, status, headers, config) {
                    if (data.status == 'OK') {
                        $scope.firstname = null;
                        $scope.lastname = null;
                        $scope.email = null;
                        $scope.phone = null;
                        $scope.comments = null;
                        $scope.messages = data.info;
                        $scope.submitted = false;
                    } else {
                        $scope.messages = 'Oops, we received your request, but there was an error processing it.';
                        $log.error(data);
                    }
                    })
                .error(function(data, status, headers, config) {
                        $scope.progress = data;
                        $scope.messages = 'There was a network error. Try again later.';
                        $log.error(data);
                    })
                .finally(function() {
                    // Hide status messages after three seconds.
                    $timeout(function() {
                        $scope.messages = null;
                    }, 3000);
                    });

                $promise = null;
                // Track the request and show its progress to the user.
                //$scope.progress.addPromise($promise);
            };
    });
 
})();
// UNCOMMENT IT IN PRODUCTION
//
// (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
// (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
// m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
// })(window,document,'script','https://www.google-analytics.com/analytics.js','ga');

// ga('create', 'UA-3420651-10', 'auto');
// ga('send', 'pageview');

(function () {
    
//    var app = angular.module('grub.desi.admin', ['ngRoute']);
 
        app.controller('CategoryAdminController',  function ($scope, Category, toaster, Upload, $timeout) {

        

        $scope.tagTransform = function (newTag) {
            var item = {
                categoryName: newTag
            };
            return item;
        };

        
        var refresh = function() {
            $scope.categories = Category.query();
            $scope.category = new Category();
        }

        refresh();
        
        $scope.add = function(category) {
            Category.save(category,function(category){
                refresh();
            });
        };
        
        $scope.update = function(category) {
            category.$update(function(){
                refresh();
            }); 
        };
        
        $scope.remove = function(category) {
            category.$delete(function(){
                refresh();
            });
        };

        
        $scope.edit = function(category) {

            $scope.category = category;
        };  
        
        $scope.reset = function(){
            refresh();
        }



        $scope.removeAll = function(){
            for(var i=0;i<$scope.categories.length;i++)
                $scope.categories[i].$delete(1);
            refresh();
        };
                
        $scope.deselect = function() {
            refresh();
        }
        });

    
})();




(function () {
    
//    var app = angular.module('grub.desi.admin', ['ngRoute']);
 
        app.controller('MenuAdminController',  function ($scope, Menu, Category,MenuMaster,Portion,  toaster, Upload, $timeout) {



            $scope.upload = function (file,callback) {
                    Upload.upload({
                                url: '/api/v1/menu/image', //webAPI exposed to upload the file
                                data:{file:file} //pass file as data, should be user ng-model
                            }).progress(function(evt) {
                            }).success(function(response, status, headers, config) {
                                callback(response);
                            }).error(function(response, status, headers, config) {
                                callback(null);// do something
                            }).xhr(function(xhr) {
                                // to abort, use ng-click like: ng-click="abort()"
                                $scope.abort = function() {
                                    xhr.abort();
                                };
                            });
                };        
            
            var refresh = function() {
                $scope.menus = Menu.query(); 
                $scope.categories = Category.query();
                $scope.menuMasters = MenuMaster.query();
                $scope.portions = Portion.query();
                $scope.menu = new Menu();
                $scope.menu.portion = $scope.portions;
                $scope.category = new Category();
                $scope.menuDefaultImage = 'menuDefaultImage.jpg';
                $scope.file = null;
                
            }

            refresh();
            
            $scope.add = function(menu,file) {
                if(file)
                {
                    $scope.upload(file,function(filename){
                        menu.imageFilename = filename;
                        Menu.save(menu,function(menu){
                            refresh();
                        });
                        
                    });
                }
                else
                {
                    Menu.save(menu,function(menu){
                        refresh();
                    });
                }
            };
            
            $scope.update = function(menu,file) {

                if(file)
                {
                    $scope.upload(file,function(filename){
                        menu.imageFilename = filename;
                        menu.$update(function(){
                            refresh();
                        }); 
                    });
                }
                else
                {
                    menu.$update(function(){
                        refresh();
                    }); 
                }
            };
            
            $scope.remove = function(menu) {
                menu.$delete(function(){
                    refresh();
                });
            };

            
            $scope.edit = function(menu) {

                $scope.menu = menu;
            
            };  
            
            $scope.reset = function(){
                refresh();
            }



            $scope.removeAll = function(){
                for(var i=0;i<$scope.menus.length;i++)
                    $scope.menus[i].$delete(1);
                refresh();
            };
                    
            $scope.deselect = function() {
                refresh();
            }




            $scope.getValuesFor = function(prop) {
                return ($scope.menus || []).
                map(function (item) { return item[prop]; }).
                filter(function (value, idx, arr) { return arr.indexOf(value) === idx; });
            }
        
            $scope.greaterThan = function(prop, val){
                return function(item){
                    return item[prop] > val;
                }
            }


            $scope.selectedMenus = function(){
                return ($scope.menus || []).
                filter(function(value,idx,arr){
                    return arr.indexOf(value) == idx;
                });
            }

            $scope.tagTransform = function (newTag) {
                var item = {
                    categoryName: newTag
                };
                return item;
            };





        });

       
          
    
})();




(function () {
    
//    var app = angular.module('grub.desi.admin', ['ngRoute']);
 
        app.controller('MenuMasterAdminController',  function ($scope, MenuMaster,  toaster, Upload, $timeout) {

        

        $scope.tagTransform = function (newTag) {
            var item = {
                menuMasterName: newTag
            };
            return item;
        };

        
        var refresh = function() {
            $scope.menuMasters = MenuMaster.query();
            $scope.menuMaster = new MenuMaster();
        }

        refresh();
        
        $scope.add = function(menuMaster) {
            MenuMaster.save(menuMaster,function(menuMaster){
                refresh();
            });
        };
        
        $scope.update = function(menuMaster) {
            menuMaster.$update(function(){
                refresh();
            }); 
        };
        
        $scope.remove = function(menuMaster) {
            menuMaster.$delete(function(){
                refresh();
            });
        };

        
        $scope.edit = function(menuMaster) {

            $scope.menuMaster = menuMaster;
        };  
        
        $scope.reset = function(){
            refresh();
        }



        $scope.removeAll = function(){
            for(var i=0;i<$scope.menuMasters.length;i++)
                $scope.menuMasters[i].$delete(1);
            refresh();
        };
                
        $scope.deselect = function() {
            refresh();
        }
        });

    
})();




(function () {
    
//    var app = angular.module('grub.desi.admin', ['ngRoute']);
 
        app.controller('PortionAdminController',  function ($scope, Portion,  toaster, Upload, $timeout) {

        

        $scope.tagTransform = function (newTag) {
            var item = {
                portionName: newTag
            };
            return item;
        };

        
        var refresh = function() {
            $scope.portions = Portion.query();
            $scope.portion = new Portion();
        }

        refresh();
        
        $scope.add = function(portion) {
            Portion.save(portion,function(portion){
                refresh();
            });
        };
        
        $scope.update = function(portion) {
            portion.$update(function(){
                refresh();
            }); 
        };
        
        $scope.remove = function(portion) {
            portion.$delete(function(){
                refresh();
            });
        };

        
        $scope.edit = function(portion) {

            $scope.portion = portion;
        };  
        
        $scope.reset = function(){
            refresh();
        }



        $scope.removeAll = function(){
            for(var i=0;i<$scope.portions.length;i++)
                $scope.portions[i].$delete(1);
            refresh();
        };
                
        $scope.deselect = function() {
            refresh();
        }
        });

    
})();



