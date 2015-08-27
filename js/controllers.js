/**
 * INSPINIA - Responsive Admin Theme
 *
 */

/**
 * MainCtrl - controller
 */
function MainCtrl() {

    this.userName = 'Example user';
    this.helloText = 'Welcome in SeedProject';
    this.descriptionText = 'It is an application skeleton for a typical AngularJS web app. You can use it to quickly bootstrap your angular webapp projects and dev environment for these projects.';

};

/**
* AddCustomerCtrl
*/
function CleanCtrl($scope,WizardHandler) {
    // Wizard 
    $scope.user = {
        firstName:  '',
        phone:      '',
        company:    '',
        email:      '',
        address:    ''
    };
    // validation
    $scope.addcustomer_submit = function() {
        if ($scope.signup_form.$valid) {
        } else {
            $scope.signup_form.submitted = true;
        }
    }
    $scope.ValidateAddCustomer1 = function() {
        if(($scope.user.firstName) && ($scope.user.phone) && ($scope.user.company) && ($scope.user.email) && ($scope.user.address)){
            WizardHandler.wizard().next();
            $(".steps-indicator li.current,.steps-indicator li.editing").removeClass("error");
        } else {
            $(".steps-indicator li.current,.steps-indicator li.editing").addClass("error");
        }
    }
};


angular
    .module('inspinia')
    .controller('MainCtrl', MainCtrl)
    .controller('CleanCtrl',CleanCtrl);