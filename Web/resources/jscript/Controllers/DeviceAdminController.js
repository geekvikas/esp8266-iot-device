(function () {
    
 
        app.controller('DeviceAdminController',  function ($scope, Device,  toaster, Upload, $timeout) {

        

        $scope.tagTransform = function (newTag) {
            var item = {
                deviceName: newTag
            };
            return item;
        };

        
        var refresh = function() {
            $scope.devices = Device.query();
            $scope.device = new Device();
        }

        refresh();
        
        $scope.add = function(device) {
            Device.save(device,function(device){
                refresh();
            });
        };
        
        $scope.update = function(device) {
            device.$update(function(){
                refresh();
            }); 
        };
        
        $scope.remove = function(device) {
            device.$delete(function(){
                refresh();
            });
        };

        
        $scope.edit = function(device) {

            $scope.device = device;
        };  
        
        $scope.reset = function(){
            refresh();
        }



        $scope.removeAll = function(){
            for(var i=0;i<$scope.devices.length;i++)
                $scope.devices[i].$delete(1);
            refresh();
        };
                
        $scope.deselect = function() {
            refresh();
        }
        });

    
})();



