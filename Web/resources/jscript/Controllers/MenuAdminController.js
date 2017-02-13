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



