var mongoose = require('mongoose');
mongoose.Promise = global.Promise;

var state = {
  db: null
}

exports.connect = function(url, done) {
  if (state.db) return done();

  mongoose.connect(url, function(err, db) {
    if (err) return done(err);
    state.db = db;
    done();
  });
}

exports.get = function() {
  return state.db;
}

exports.close = function(done) {
  if (state.db) {
    state.db.disconnect(function(err, result) {
      state.db = null;
      done(err);
    })
  }
}