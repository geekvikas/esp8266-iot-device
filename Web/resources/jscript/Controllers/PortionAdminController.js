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



