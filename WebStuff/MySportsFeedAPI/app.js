var bodyParser = require("body-parser");
var express = require("express");
var path = require("path");
var app = express();

var routes = require("./routes");

app.use('/', express.static('./'));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app.use(routes);

app.set("port", process.env.PORT || 3000);
app.listen(app.get("port"), function() {
  console.log("Server started on port " + app.get("port"));
});

