var gulp = require('gulp');
var sass = require('gulp-sass');
var notify = require('gulp-notify');
var bower = require('gulp-bower');
var sourcemaps = require('gulp-sourcemaps');
var concat =  require('gulp-concat');
var gutil =  require('gulp-util');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');
var clean = require('gulp-clean-css');

var config = {
    clientPath: './public',
    fontsPath: './resources/fonts',
    sassPath: './resources/sass',
    jsPath: './resources/jscript',
    bowerDir: './bower_components'
}

gulp.task('bower', function() {
    return bower()
        .pipe(gulp.dest(config.bowerDir))
});

gulp.task('build-fonts', function() {
    return gulp.src([
        config.bowerDir + '/font-awesome/fonts/**.*',
        config.bowerDir + '/bootstrap-sass/assets/fonts/**/*.*',
        config.fontsPath + '/**.*',
        
    ])
        .pipe(gulp.dest(config.clientPath + '/fonts'));
});


gulp.task('build-css', function() {
    gulp.src([ 
                    config.bowerDir + '/angularjs-toaster/toaster.css',
                    config.bowerDir + '/angular-ui-select/dist/select.css',
                ])
    .pipe(clean())
    .pipe(rename({suffix: '.min'}))
    .pipe(gulp.dest(config.clientPath + '/css/lib/',{}));

    gulp.src(config.sassPath  + '/**/*.*')
        .pipe(sass({includePaths: [
                config.sassPath ,
                config.bowerDir + '/bootstrap-sass/assets/stylesheets/',
                config.bowerDir + '/font-awesome/scss',
                config.bowerDir + '/bootstrap-select/sass',
            ]}))
        .pipe(concat('style.css'))
        .pipe(sass().on('error', sass.logError))
        //.pipe(clean()) 
        .pipe(rename({suffix: '.min'}))
        .pipe(gulp.dest(config.clientPath + '/css'));
});


gulp.task('build-js', function() {
  return gulp.src([
                    config.jsPath + '/AngularApplication.js',
                    config.jsPath + '/**/*.js'
                    ])
    //.pipe(sourcemaps.init())
    .pipe(concat('bundle.js'))
      //only uglify if gulp is ran with '--type production'
    //.pipe(uglify()) 
    //.pipe(sourcemaps.write())
    //.pipe(rename({suffix: ''}))
    .pipe(gulp.dest(config.clientPath + '/js'));
});


gulp.task('copy-js-libs', function() {
        gulp.src([ 
                        config.bowerDir + '/bluebird/js/browser/bluebird.min.js',
                        config.bowerDir + '/jquery/dist/jquery.min.js',
                        config.bowerDir + '/angular-ui-select/dist/select.min.js',
                        config.bowerDir + '/ng-file-upload/ng-file-upload.min.js',
                        config.jsPath + '/../jslib/pace.min.js',
                        
                    ])
        .pipe(gulp.dest(config.clientPath + '/js/lib/',{}));

        gulp.src([ 
                        config.bowerDir + '/angular/angular.min.js',
                        config.bowerDir + '/angular-sanitize/angular-sanitize.min.js',
                        config.bowerDir + '/angular-route/angular-route.min.js',
                        config.bowerDir + '/angular-resource/angular-resource.min.js',
                        config.bowerDir + '/angular-animate/angular-animate.min.js',
                        config.bowerDir + '/angular-filter/dist/angular-filter.min.js',
                        config.bowerDir + '/angularjs-toaster/toaster.min.js',
                        ])
        .pipe(sourcemaps.init())
        .pipe(concat('angular-bundle.min.js',{newLine: '\n\n/* ----- FILE   SEPERATOR ----- */\n\n'}))
        .pipe(sourcemaps.write())
        .pipe(gulp.dest(config.clientPath + '/js/lib/',{}));
        

        gulp.src([ 
                        config.bowerDir + '/bootstrap/dist/js/bootstrap.min.js',
                        config.bowerDir + '/bootstrap-select/dist/js/bootstrap-select.min.js'])
        .pipe(concat('bootstrap-bundle.min.js'))
        .pipe(gulp.dest(config.clientPath + '/js/lib/',{}));
        
        return;
});

// Rerun the task when a file changes
gulp.task('watch', function() {
    gulp.watch(config.sassPath + '/**/*.*', ['build-css']);
    gulp.watch(config.jsPath + '/**/*.*', ['build-js']);
    gulp.watch(config.fontsPath + '/**/*.*', ['build-fonts']);
});

gulp.task('default', ['bower', 'build-fonts','build-css','build-js','copy-js-libs']);
