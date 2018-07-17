var express = require("express");
var router = express.Router();

router.get("/", function (request, response) {
    response.sendFile(__dirname + "/public/views/index.html");
});

function callbackfs() {
    console.log("The file was saved!");
}
//////////////////DATA//BASE//HANDLING//////////////////////////////
const myDatabase = require('./myDatabase');

let db = new myDatabase();

//Use getAllObjects.
router.get('/read', function (req, res) {
    let objs = db.getAllObjects();
    res.json(objs);
});

//Use getObjectWithID and change index to ident.
router.get('/read/:ident', function (req, res) {
    res.json(db.getObjectWithID(req.params.ident));
});

//Use addObject and no need for index.
//                ident should be part of object.
router.post('/create', function (req, res) {
    if (req.body.name == "") {
        res.json(null);
        return;
    }
    let obj = {
        name: req.body.name,
        ident: req.body.ident
    };
    res.json(db.addObject(obj));
});

//  Use changeObject and no need for index.
//                ident should be part of object.
router.put('/update', function (req, res) {
    if (req.body.name == "") {
        res.json(null);
        return;
    }
    let obj = {
        name: req.body.name,
        ident: req.body.ident
    };
    res.json(db.changeObject(obj));
});

//add or modify.  Use deleteObjectWithID and change index to ident.
router.delete('/delete/:ident', function (req, res) {
    res.json(db.deleteObjectWithID(req.params.ident));
});
///////////////END//DATA//BASE//HANDLING////////////////////////////



module.exports = router;
