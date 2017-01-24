var express = require('express');
var router = express.Router();
var path = require('path');
var LATEST_VERSION = 0.16;

/* GET users listing. */
// router.get('/data', function(req, res, next) {
//   console.log(JSON.stringify(req.headers));
//   res.status(200);
//   res.sendFile(path.join(__dirname, '../fwupdate', 'data.bin'));
// });

router.get('/getTime', function(req, res, next) {
        res.status(200).send((new Date).getTime().toString());
});
  
module.exports = router;
