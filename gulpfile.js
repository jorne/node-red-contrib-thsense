var gulp = require('gulp');
var nodemon = require('gulp-nodemon');

gulp.task("start", function () {
  nodemon({
    exec: "./node_modules/node-red/red.js -v --userDir ./.node-red --settings ./.node-red/settings.js",
    ext: "js html",
    env: { "NODE_ENV": "development" }
  });
});
