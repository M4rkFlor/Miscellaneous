var express = require("express");
var router = express.Router();

var sports = require('./sportsModule');
sports('andrewyates', 'T4pQsEYsxXop');
//sports('mvhscs1:Asdfghjk!1');

router.get("/",function(request,response){
    response.sendFile(__dirname + "/index.html");
});

////////////////////////////////////

router.get("/request/nhl", function(req, res, next) {
	sports.NHL.getActivePlayers( function (err, obj) {
    		if (err) {
        		return console.log('Error occurred active_players: ' + err);
    		}
var result = JSON.stringify(obj);
console.log(result);
//console.log(result[0].stats.GamesPlayed['#text']);
		res.json({"info":obj});
	});
});
////////////////////////////////////

router.get("/request/nba", function(req, res, next) {
	sports.NBA.getActivePlayers( function (err, obj) {
    		if (err) {
        		return console.log('Error occurred active_players: ' + err);
    		}
var result = JSON.stringify(obj);
console.log(result);
//console.log(result[0].stats.GamesPlayed['#text']);
		res.json({"info":obj});
	});
});
////////////////////////////////////

router.get("/request/nba/:name", function(req, res, next) {
	sports.NBA.getPlayer(req.params.name, function (err, obj) {
    		if (err) {
        		return console.log('Error occurred active_players: ' + err);
    		}
var result = JSON.stringify(obj);
console.log(result);

//console.log(obj[0].player);

//console.log(obj[0].stats.GamesPlayed['#text']);
		res.json({"info":obj});
	});
});

////////////////////////////////////

router.get("/request/nba/stats/:name", function(req, res, next) {
	sports.NBA.getPlayerStats(req.params.name, function (err, obj) {
    		if (err) {
        		return console.log('Error occurred active_players: ' + err);
    		}
var result = JSON.stringify(obj);
//console.log(result);

//console.log(obj[0].player);

//console.log(obj[0].stats.GamesPlayed['#text']);
		res.json({"info":obj});
	});
});



////////////////////////////////////

router.use(function(req,res,next) {
	next();
});

router.use(function(req,res) {
	res.statusCode = 404;
	res.end("404!");
});

module.exports = router;
