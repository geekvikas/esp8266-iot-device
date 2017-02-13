var mongoose = require('mongoose');
var Schema = mongoose.Schema;
//var imageWithThumbnail = require('./image-with-thumbnail').schema;

var schema = new Schema(
    {
        menuName: {type:String, required: true},
        menuDescription: {type:String, required: false},
        isTag: {type:Boolean, required:false}
    }
);


module.exports = mongoose.model('MenuMaster',schema);
exports.schema = schema;
