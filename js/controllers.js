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

function listmanagementCtrl ($scope) {
     $scope.options = [
        { name: 'Select bulk action', value: 'listmanagement.list' }, 
        { name: 'Merge', value: 'listmanagement.merge' }, 
        { name: 'Keep', value: 'listmanagement.keep' }, 
        { name: 'Remove', value: 'listmanagement.remove' }, 
    ];
    $scope.form = {type : $scope.options[0].value};
}


function ionSlider() {
    this.ionSliderOptions1 = {
        min: 0,
        max: 5000,
        type: 'single',
        prefix: "Amount: ",
        maxPostfix: "+",
        prettify: false,
        hasGrid: true
    };
    this.ionSliderOptions2 = {
        min: 0,
        max: 5000,
        type: 'single',
        prefix: "Star: ",
        maxPostfix: "+",
        prettify: false,
        hasGrid: true
    };
    this.ionSliderOptions3 = {
        min: 0,
        max: 5000,
        type: 'single',
        prefix: "Random amount: ",
        maxPostfix: "+",
        prettify: false,
        hasGrid: true
    };
   
}


angular
    .module('inspinia')
    .controller('MainCtrl', MainCtrl)
    .controller('CleanCtrl',CleanCtrl)
    .controller('ionSlider',ionSlider)
    .controller('listmanagementCtrl',listmanagementCtrl);