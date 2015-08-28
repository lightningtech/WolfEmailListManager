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
* CleanCtrl
*/
function CleanCtrl($scope,WizardHandler,FileUploader) {
    $scope.fileprocess = false
    var uploader = $scope.uploader = new FileUploader();
    uploader.onAfterAddingAll = function(addedFileItems) {
        $scope.fileprocess = true
    };
};

function listmanagementCtrl ($scope,$state) {
    // select bulk
    $scope.optionsbulk = [
        { label: 'Select bulk action', value: 'listmanagement.list' }, 
        { label: 'Merge', value: 'listmanagement.merge' }, 
        { label: 'Keep', value: 'listmanagement.keep' }, 
        { label: 'Remove', value: 'listmanagement.remove' }, 
    ];
    $scope.selectbulk = {url : $scope.optionsbulk[0].value};
    $scope.locationChangebulk = function(){
         $state.go($scope.selectbulk.url);
    }
    // select individual
    $scope.optionsindividual = [
        { label: 'Select bulk action', value: 'listmanagement.list' }, 
        { label: 'Separate list', value: 'listmanagement.separate' }, 
        { label: 'Make sample', value: 'listmanagement.makesample' }, 
        { label: 'Split list', value: 'listmanagement.split' }, 
    ];
    $scope.selectindividual = {url : $scope.optionsindividual[0].value};
    $scope.locationChangeindividual = function(){
         $state.go($scope.selectindividual.url);
    }
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

function addcleanCtrl ($scope,FileUploader) {
    $scope.uploader = new FileUploader();
}

angular
    .module('inspinia')
    .controller('MainCtrl', MainCtrl)
    .controller('CleanCtrl',CleanCtrl)
    .controller('ionSlider',ionSlider)
    .controller('listmanagementCtrl',listmanagementCtrl);