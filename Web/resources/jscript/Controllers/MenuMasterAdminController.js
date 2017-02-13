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



