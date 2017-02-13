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



