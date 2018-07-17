var bcrypt = require("bcrypt-nodejs");
var SALT_FACTOR = 10;

var mongoose = require("mongoose");

var infSchema = mongoose.Schema({
  name: { type: String, required: true, unique: true },
    sessionName:{ type: String, required: true }
});


var Info = mongoose.model("infos ", infSchema);

module.exports = Info;

