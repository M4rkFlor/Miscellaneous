var fs = require('fs');


function writeToDB(usersdata) {

    fs.writeFile("Users.txt", JSON.stringify(usersdata), function (err) {
        if (err) {
            console.log("Error occured in saving DB");
            return console.log(err);
        }

        console.log("The file was saved in the mydatabase!");
    });
}
//var buf = Buffer.from(JSON.stringify(obj));
//And for converting string to json obj :

//var temp = JSON.parse(buf.toString());
function readuserTXTFromDB() {

    fs.readFile('./Users.txt', "utf-8", function read(err, data) {
        if (err) {
            throw err;
        }
        this.infoList = data;
        console.log("these Users Have been loaded: " + this.infoList);
    });
}
let myDatabase = function () {
    //load txt file 
    //insert txt data into infolist
    //change the bellow to data read from txt
    //this.infoList = [];
    readuserTXTFromDB();
}
myDatabase.prototype.getArraySize = function () {
    return this.infoList.length;
}

//add or modify.  Complete getAllObjects function.
myDatabase.prototype.getAllObjects = function () {
    return (this.infoList);
}


myDatabase.prototype.getAllNames = function () {
    let names = [];
    for (let i = 0; i < this.infoList.length; i++) {
        if (this.infoList[i]) {
            names.push(this.infoList[i].name);
        }
    }
    return (names);
}

myDatabase.prototype.getObjectAtIndex = function (index) {
    if (index < 0 || index >= this.infoList.length)
        return (null);
    else {
        if (!this.infoList[index]) {
            return (null);
        } else {
            return (this.infoList[index]);
        }
    }
}

myDatabase.prototype.getObjectWithID = function (ident) {
    for (let i = 0; i < this.infoList.length; i++) {
        if (this.infoList[i] && ident == this.infoList[i].ident)
            return (this.infoList[i]);
    }
    return (null);
}

myDatabase.prototype.addObjectAtIndex = function (obj, index) {
    if (index < 0)
        return (null);
    if (index < this.infoList.length) {
        if (!this.infoList[index]) {
            this.infoList[index] = obj;
            return (obj);
        } else {
            return (null);
        }
    } else
        this.infoList[index] = obj;
    return (obj);
}


myDatabase.prototype.addObject = function (obj) {
    for (let i = 0; i < this.infoList.length; i++) {
        if (this.infoList[i] && obj.ident == this.infoList[i].ident)
            return (null);
    }
    this.infoList.push(obj);
    console.log(this.infoList);
    writeToDB(this.infoList);
    return (obj);
}




myDatabase.prototype.changeObjectAtIndex = function (obj, index) {
    if (index < 0 || index >= this.infoList.length)
        if (!this.infoList[index])
            return (null);
    this.infoList[index] = obj;
    return (obj);
}

//  Complete changeObject function.
myDatabase.prototype.changeObject = function (obj) {
    //check if objexists if it dose change it else return null
    for (let i = 0; i < this.infoList.length; i++) {
        if (this.infoList[i] && obj.ident == this.infoList[i].ident) {
            this.infoList[i] = null;
            this.infoList[i] = obj;
            //this.infoList.push(obj);
            return (obj);
        }
    }
    return (null);
}

myDatabase.prototype.deleteObjectAtIndex = function (index) {
    if (index < 0 || index >= this.infoList.length) {
        return (null);
    } else {
        if (!this.infoList[index]) {
            return (null);
        } else {
            let obj = this.infoList[index];
            this.infoList[index] = null;
            return (obj);
        }
    }
}


//add or modify.  Complete deleteObjectWithID function.
myDatabase.prototype.deleteObjectWithID = function (ident) {
    for (let i = 0; i < this.infoList.length; i++) {
        if (this.infoList[i] && ident == this.infoList[i].ident) {
            this.infoList[i] = null;
            return (null);
        }
    }
    return (ident);

}
module.exports = myDatabase;
