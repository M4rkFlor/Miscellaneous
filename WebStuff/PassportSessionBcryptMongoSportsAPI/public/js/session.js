var userSessionName;

function logoutClicked() {
    $.get("/logout", function (data) {
        window.location = data.redirect;
    });
    return false;
}


function createClicked() {
    if ($("#ident").val() == "") {
        alert("ERROR");
        return false;
    }

    $.ajax({
        url: "/people",
        type: "POST",
        data: {
            name: $("#teamname").val(),
            sessionName: userSessionName
        },
        success: function (data) {
            if (!data)
                alert("ERROR");
            else {
                alert("CREATE VALID");
                $.get("/loadteams", function (data) {
                    for (let i = 0; i < data.length; i++) {
                        $('#PlayerSelect').append($('<option>', {
                            value: data[i].name,
                            text: data[i].name
                        }));
                    }
                });
            }

        },
        dataType: "json"
    });
    return false;
}

//////
function success(data) {

    $("#list").empty();

    console.log(data.info);

    for (let i = 0; i < data.info.length; i++) {
        $("#list").append("<li>" + data.info[i].player.FirstName + " " + data.info[i].player.LastName + " " + data.info[i].player.Height + "</li>");
    }

}

function success2(data) {

    $("#list").empty();
    $("#list").append("<li>" + data.info[0].player.FirstName + " " + data.info[0].player.LastName + " " + data.info[0].player.Height + "</li>");
}


function success3(data) {
    console.log("sucsess3");
    console.log(data.info);

    console.log(data.info[0].player.FirstName);

    console.log(data.info[0].stats.Pts['#text']);


    $("#list").empty();
    $("#list").append("<li>" + data.info[0].player.FirstName + " " + data.info[0].player.LastName + " Points = " + data.info[0].stats.Pts['#text'] + "</li>");


}

//stats[i].stats.Pts['#text']

function requestClickedDisplay() {
    //send an HTTP get request and get a result back.
    $.get("/request/nba/stats/" + $('#PlayerSelect').find(":selected").text(), success3);
    return false;
}

function requestClickedNBA() {
    //send an HTTP get request and get a result back.
    $.get("/request/nba", success);
    return false;
}

function requestClickedNBAPlayer() {
    //send an HTTP get request and get a result back.
    $.get("/request/nba/" + $("#name").val(), success2);
    return false;
}

function requestClickedNBAPlayerStats() {
    //send an HTTP get request and get a result back.
    $.get("/request/nba/stats/" + $("#name").val(), success3);
    return false;
}



$(document).ready(function () {

    $.get("/userInfo", function (data) {
        if (data.username) {
            userSessionName = data.username;
            $("#session").html("Session " + data.username);
        }

    });

    $.get("/loadteams", function (data) {
        console.log(data);
        console.log("^Loadteams^");
        for (let i = 0; i < data.length; i++) {
            $('#PlayerSelect').append($('<option>', {
                value: data[i].name,
                text: data[i].name
            }));
        }
    });

    $("#logout").click(logoutClicked);

    $("#requestButtonDisplay").click(requestClickedDisplay);
    $("#createButton").click(createClicked);

});
