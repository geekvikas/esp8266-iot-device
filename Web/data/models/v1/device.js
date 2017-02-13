var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var firmwareInfo = {
        version: {type:String, required: true},
        flavor: {type:String, required: false},
        timestamp: {type:String, required: true},
        comments: {type:String, required: false}
    };

var deviceInfo = {
		deviceId: {type:String, required: false},
		vcc: {type:String, required: false},
		freeHeap: {type:String, required: false},
		bootMode: {type:String, required: false},
		cpuFreq: {type:String, required: false},
		chipId: {type:String, required: true},
		sdkVersion: {type:String, required: true},
		coreVersion: {type:String, required: true},
		bootVersion: {type:String, required: true},
		flashChipId: {type:String, required: true},
		flashChipRealSize: {type:String, required: false},
		flashChipSize: {type:String, required: false},
		flashChipSpeed: {type:String, required: false},
		flashChipMode: {type:String, required: false},
		flashChipSizeByChipId: {type:String, required: false},
		sketchSize: {type:String, required: false},
		sketchMD5: {type:String, required: true},
		resetReason: {type:String, required: false},
		resetInfo: {type:String, required: false}
    };

var schema = new Schema(
    {
        firmwareInfo: firmwareInfo,
        deviceInfo: deviceInfo
    }
);


module.exports = mongoose.model('Device',schema);

