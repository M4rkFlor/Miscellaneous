/* add or modify.
   change index to ident.
   when you select Read with no ident, display the ident and the name.
*/
function readClicked() {
    if ($("#ident").val() == "") {
        $.ajax({
            url: "/read",
            type: "GET",
            success: function (data) {
                if (!data)
                    alert("ERROR data");
                else {

                    $("#list").empty();

                    for (let i = 0; i < data.length; i++) {
                        $("#list").append("<li>" + data[i].name + "</li>");
                        $("#list").append("<li>" + data[i].ident + "</li>");
                    }

                }
            },
            dataType: "json"
        });
    } else {
        $.ajax({
            url: "/read/" + $("#ident").val(),
            type: "GET",
            success: function (data) {
                if (!data)
                    alert("ERROR data");
                else {
                    $("#list").empty();
                    $("#name").val(data.name);
                }

            },
            dataType: "json"
        });
    }
    return false;
}

function createClicked() {
    if ($("#ident").val() == "") {
        alert("ERROR");
        return false;
    }

    $.ajax({
        url: "/create",
        type: "POST",
        data: {
            ident: Number($("#ident").val()),
            name: $("#name").val()
        },
        success: function (data) {
            if (!data)
                alert("ERROR");
            else
                alert("CREATE VALID");
        },
        dataType: "json"
    });
    return false;
}

function updateClicked() {

    if ($("#ident").val() == "") {
        alert("ERROR");
        return false;
    }
    $.ajax({
        url: "/update",
        type: "PUT",
        data: {
            ident: Number($("#ident").val()),
            name: $("#name").val()
        },
        success: function (data) {
            if (!data)
                alert("ERROR");
            else
                alert("UPDATE VALID");
        },
        dataType: "json"
    });
    return false;
}


function deleteClicked() {
    $.ajax({
        url: "/delete/" + Number($("#ident").val()),
        type: "DELETE",
        success: function (data) {
            if (!data)
                alert("GOOD DELETE");
            else
                alert("NO DELETE");
        },
        dataType: "json"
    });
    return false;
}

$(document).ready(function () {

    $("#name").keydown(function (event) {
        if (event.which === 13) {
            createClicked();
            event.preventDefault();
            return false;
        }
    });

    $("#ident").keydown(function (event) {
        if (event.which === 13) {
            readClicked();
            event.preventDefault();
            return false;
        }
    });

    $("#readButton").click(readClicked);
    $("#createButton").click(createClicked);
    $("#updateButton").click(updateClicked);
    $("#deleteButton").click(deleteClicked);

});
