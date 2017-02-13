var mongoose = require('mongoose');
var Schema = mongoose.Schema;


var schema = new Schema(
    {
        portionName: {type:String, required: true},
        portionDescription: {type:String, required: false},
        portionPrice: {type:String, required: false},
        isTag: {type:Boolean, required:false}
    }
);


module.exports = mongoose.model('Portion',schema);
exports.schema = schema;
