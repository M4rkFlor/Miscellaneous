
var express = require("express");
var router = express.Router();

router.get("/",function(request,response){
	response.sendFile(__dirname + "/index.html");
});

module.exports = router;

