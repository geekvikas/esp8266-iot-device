var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var categorySchema = require('./category').schema;
var portionSchema = require('./portion').schema;

//var imageWithThumbnail = require('./image-with-thumbnail').schema;

var schema = new Schema(
    {
        menuName: {type:String, required: true},
        category: [categorySchema],
        itemName: {type:String, required: true},
        itemDescription: {type:String, required: false},
        portion:  [portionSchema],
        imageFilename: {type:String, required: false}
    }
);


module.exports = mongoose.model('Menu',schema);

