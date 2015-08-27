/**
 * INSPINIA - Responsive Admin Theme
 *
 * Inspinia theme use AngularUI Router to manage routing and views
 * Each view are defined as state.
 * Initial there are written state for all view in theme.
 *
 */
function config($stateProvider, $urlRouterProvider, $ocLazyLoadProvider) {
    $urlRouterProvider.otherwise("/index/main");

    $ocLazyLoadProvider.config({
        // Set to true if you want to see what and when is dynamically loaded
        debug: false
    });

    $stateProvider
        /*
            DASHBOARD SETTING
        */
        .state('index', {
            abstract: true,
            url: "/index",
            templateUrl: "views/common/content.html",
        })
        .state('index.main', {
            url: "/main",
            templateUrl: "views/main.html",
            data: { pageTitle: 'Example view' }
        })
        /*
            PROFILE SETTINGS
        */
        .state('profile', {
            abstract: true,
            url: "/profile",
            templateUrl: "views/common/content.html",
        })
        .state('profile.view', {
            url: "/view.html",
            templateUrl: "views/profile/view.html",
            data: { pageTitle: 'Profile' }
        })
        .state('profile.edit', {
            url: "/edit.html",
            templateUrl: "views/profile/edit.html",
            data: { pageTitle: 'Edit profile' },
            resolve: {
                loadPlugin: function ($ocLazyLoad) {
                    return $ocLazyLoad.load([
                        
                        {
                            files: ['js/plugins/jasny-bootstrap/js/jasny-bootstrap.min.js','js/plugins/jasny-bootstrap/css/jasny-bootstrap.min.css']
                        }

                    ]);
                }
            }
        })
        .state('profile.help', {
            url: "/help.html",
            templateUrl: "views/profile/help.html",
            data: { pageTitle: 'Help' },
        })
        /*
            EXTRACT AND CLEAN EMAIL SETTINGS
        */
        .state('clean', {
            abstract: true,
            url: "/clean",
            templateUrl: "views/common/content.html",
        })
        .state('clean.add', {
            url: "/add.html",
            templateUrl: "views/clean/add.html",
            data: { pageTitle: 'Extract and clean email' }
            ,resolve: {
                loadPlugin: function ($ocLazyLoad) {
                    return $ocLazyLoad.load([
                        {
                            insertBefore: '#loadBefore',
                            name: 'localytics.directives',
                            files: ['css/plugins/chosen/chosen.css','js/plugins/chosen/chosen.jquery.js','js/plugins/chosen/chosen.js']
                        },
                        {
                            serie: true,
                            files: ['js/plugins/dataTables/jquery.dataTables.js','css/plugins/dataTables/dataTables.bootstrap.css']
                        },
                        {
                            serie: true,
                            files: ['js/plugins/dataTables/dataTables.bootstrap.js']
                        },
                        {
                            name: 'datatables',
                            files: ['js/plugins/dataTables/angular-datatables.min.js']
                        },
                        {
                            files: ['css/plugins/awesome-bootstrap-checkbox/awesome-bootstrap-checkbox.css']
                        }
                    ]);
                }
            }
        })
        /*
            LIST MANAGEMENT SETTING
        */
        .state('listmanagement', {
            abstract: true,
            url: "/listmanagement",
            templateUrl: "views/common/content.html",
        })
        .state('listmanagement.list', {
            url: "/list.html",
            templateUrl: "views/listmanagement/list.html",
            data: { pageTitle: 'List Management' },
            resolve: {
                loadPlugin: function ($ocLazyLoad) {
                    return $ocLazyLoad.load([
                        {
                            insertBefore: '#loadBefore',
                            name: 'localytics.directives',
                            files: ['css/plugins/chosen/chosen.css','js/plugins/chosen/chosen.jquery.js','js/plugins/chosen/chosen.js']
                        },
                        {
                            serie: true,
                            files: ['js/plugins/dataTables/jquery.dataTables.js','css/plugins/dataTables/dataTables.bootstrap.css']
                        },
                        {
                            serie: true,
                            files: ['js/plugins/dataTables/dataTables.bootstrap.js']
                        },
                        {
                            name: 'datatables',
                            files: ['js/plugins/dataTables/angular-datatables.min.js']
                        },
                        {
                            files: ['css/plugins/awesome-bootstrap-checkbox/awesome-bootstrap-checkbox.css']
                        }
                    ]);
                }
            }
        })
        /*
            TEMPLATE SETTINGS 
            NOTE: JUST FOR DEMO
        */ 
        .state('login', {
            url: "/login",
            templateUrl: "views/login/login.html",
            data: { pageTitle: 'Login', specialClass: 'gray-bg' }
        })
        .state('register', {
            url: "/register",
            templateUrl: "views/login/register.html",
            data: { pageTitle: 'Register', specialClass: 'gray-bg' }
        })
        .state('forgot_password', {
            url: "/forgot_password",
            templateUrl: "views/login/forgot_password.html",
            data: { pageTitle: 'Forgot password', specialClass: 'gray-bg' }
        })
    ;
}
angular
    .module('inspinia')
    .config(config)
    .run(function($rootScope, $state) {
        $rootScope.$state = $state;
    });
