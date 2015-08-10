module.exports = function(grunt) {
	pkg: grunt.file.readJSON('package.json');
	grunt.initConfig({
		connect: {
			server: {
				options: {
					port: 9001,
					hostname: 'localhost',
					base: '.',										
					livereload: true
				}
			}
		},
		watch: {
			all: {
				files: '**/*',
				options: {
					livereload: true
				}
			}
		},
		php: {
			dist: {
				options: {
					port: 9001,
					hostname: 'localhost',
					base: '.',
					open: true,
					livereload: true
				}
			}
		}
	});

	grunt.loadNpmTasks('grunt-contrib-connect');
	grunt.loadNpmTasks('grunt-contrib-watch');
	grunt.loadNpmTasks('grunt-php');	

	grunt.registerTask('default', ['connect', 'php', 'watch']);
};