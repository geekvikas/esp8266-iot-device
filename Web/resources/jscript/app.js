

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