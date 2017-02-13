var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var schema = new Schema(
    {
                categoryName: {type:String, required:true},
                categoryDescription: {type:String, required:false},
                isTag: {type:Boolean, required:false}
    }
);

module.exports = mongoose.model('Category',schema);
exports.schema = schema;