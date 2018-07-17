var express = require("express");
var passport = require("passport");
var path = require("path");

var User = require("./models/user");
var Info = require("./models/info");
var router = express.Router();

var sports = require('./sportsModule');
sports('andrewyates', 'T4pQsEYsxXop');
//sports('mvhscs1:Asdfghjk!1');
//function ensureAuthenticated(req, res, next) {
//  if (req.isAuthenticated()) {
//    next();
//  } else {
//    req.flash("info", "You must be logged in to see this page.");
//    res.redirect("/login");
//  }
//}
router.use(function (req, res, next) {
    res.locals.currentUserjy = req.user;
    res.locals.errors = req.flash("error");
    res.locals.infos = req.flash("info");
    next();
});



router.get("/successroot", function (req, res) {
    console.log("get successroot");
    res.json({
        redirect: "/"
    });
});

router.get("/failroot", function (req, res) {
    console.log("get failroot");
    res.json({
        redirect: "/login"
    });
});

router.get("/successsignup", function (req, res) {
    console.log("get successsignup");
    res.json({
        redirect: "/session"
    });
});

router.get("/failsignup", function (req, res) {
    console.log("get failsignup");
    res.json({
        redirect: "/login"
    });
});

router.get("/successlogin", function (req, res) {
    console.log("get successsignup");
    res.json({
        redirect: "/session"
    });
});
router.get("/faillogin", function (req, res) {
    console.log("get failsignup");
    res.json({
        redirect: "/login"
    });

});

router.get("/", function (req, res, next) {
    console.log("get root");
    let thePath = path.resolve(__dirname, "public/views/login.html");
    res.sendFile(thePath);

    // User.find()
    // .sort({ createdAt: "descending" })
    // .exec(function(err, users) {
    //   if (err) { return next(err); }
    //   res.render("index", { users: users });
    // });
});

router.get("/signup", function (req, res) {
    console.log("get signup");

    let thePath = path.resolve(__dirname, "public/views/signup.html");
    res.sendFile(thePath);

});

router.get("/login", function (req, res) {
    console.log("get login");

    let thePath = path.resolve(__dirname, "public/views/login.html");
    res.sendFile(thePath);

});

router.get("/session", function (req, res) {
    console.log("get session");
    if (req.isAuthenticated()) {
        let thePath = path.resolve(__dirname, "public/views/session.html");
        res.sendFile(thePath);
    } else {
        let thePath = path.resolve(__dirname, "public/views/login.html");
        res.sendFile(thePath);
    }
});

router.get("/userInfo", function (req, res) {
    if (req.isAuthenticated()) {
        res.json({
            username: req.user.username
        });
    } else {
        res.json(null);
    }
});

router.get("/logout", function (req, res) {
    if (req.isAuthenticated()) {
        req.logout();
        res.redirect("/successroot");
    } else {
        res.redirect("/failroot");
    }
});

router.post("/signup", function (req, res, next) {
    console.log("post signup");

    var username = req.body.username;
    var password = req.body.password;

    User.findOne({
        username: username
    }, function (err, user) {

        if (err) {
            return next(err);
        }
        if (user) {
            req.flash("error", "User already exists");
            return res.redirect("/failsignup");
        }
        console.log("post signup1");

        let newUser = new User({
            username: username,
            password: password
        });
        console.log("post signup2");

        newUser.save(next); //this line has to be called.
        console.log("post signup done");

    });

}, passport.authenticate("login", {
    successRedirect: "/successsignup",
    failureRedirect: "/failsignup",
    failureFlash: true
}));

router.post("/login", passport.authenticate("login", {
    successRedirect: "/successlogin",
    failureRedirect: "/faillogin",
    failureFlash: true
}));
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//Databas//Connections//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//
router.post('/people', function (req, res, next) {
    console.log("doing a create");
    console.log(req.body);

    let newTeam = new Info({
        name: req.body.name,
        sessionName: req.body.sessionName
    });

    newTeam.save(next); //this line has to be called.

    res.json(newTeam);



});

router.get('/loadteams', function (req, res, next) {
    console.log("doing a loadteam for " + req.user.username);
     /*  function donefind(cb){
        console.log("cb:"+cb)
        res.json(cb);
    }
 
    Info.find({
        'sessionName': req.user.username
    }).
    exec(donefind);
    */
    Info.find(function (err, objs) {
  if (err) return console.error(err);
  console.log(objs);
        res.json(objs);
})

});
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//Sports//Routes//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓//

////////////////////////////////////

router.get("/request/nhl", function (req, res, next) {
    sports.NHL.getActivePlayers(function (err, obj) {
        if (err) {
            return console.log('Error occurred active_players: ' + err);
        }
        var result = JSON.stringify(obj);
        console.log(result);
        //console.log(result[0].stats.GamesPlayed['#text']);
        res.json({
            "info": obj
        });
    });
});
////////////////////////////////////

router.get("/request/nba", function (req, res, next) {
    sports.NBA.getActivePlayers(function (err, obj) {
        if (err) {
            return console.log('Error occurred active_players: ' + err);
        }
        var result = JSON.stringify(obj);
        console.log(result);
        //console.log(result[0].stats.GamesPlayed['#text']);
        res.json({
            "info": obj
        });
    });
});
////////////////////////////////////

router.get("/request/nba/:name", function (req, res, next) {
    sports.NBA.getPlayer(req.params.name, function (err, obj) {
        if (err) {
            return console.log('Error occurred active_players: ' + err);
        }
        var result = JSON.stringify(obj);
        console.log(result);

        //console.log(obj[0].player);

        //console.log(obj[0].stats.GamesPlayed['#text']);
        res.json({
            "info": obj
        });
    });
});

////////////////////////////////////

router.get("/request/nba/stats/:name", function (req, res, next) {
    sports.NBA.getPlayerStats(req.params.name, function (err, obj) {
        if (err) {
            return console.log('Error occurred active_players: ' + err);
        }
        var result = JSON.stringify(obj);
        console.log(result);

        console.log(obj[0].player);

        console.log(obj[0].stats.GamesPlayed['#text']);
        res.json({
            "info": obj
        });
    });

});


router.use(function (req, res, next) {
    next();
});

router.use(function (req, res) {
    res.statusCode = 404;
    res.end("404!");
});

module.exports = router;
