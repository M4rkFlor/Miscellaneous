var express = require("express");
var path = require("path");
var app = express();

app.set("port", process.env.PORT || 8080);

app.use('/', express.static('./'));

app.get("/", function(req, res, next) {
	let thePath = path.resolve(__dirname,"/index.html");		
	res.sendFile(thePath);	
});

app.listen(app.get("port"), function() {
  console.log("Server started on port " + app.get("port"));
});
