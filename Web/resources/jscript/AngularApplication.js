  var app = angular.module('ioled.admin', ['ngResource',  'ngAnimate', 'toaster','angular.filter','ngFileUpload','ui.select','ngSanitize']);

 

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
  app.factory('Device', function($resource) {
    return $resource('/api/v1/device/:id', { id: '@_id' }, {
      update: { // We need to define this method manually as it is not provided with ng-resource
        method: 'PUT'
      }
    });
  });

  
