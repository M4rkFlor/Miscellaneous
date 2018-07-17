/* add or modify.
   change index to ident.
   when you select Read with no ident, display the ident and the name.
*/
  		function readClicked(){
        if ($("#ident").val() == "") {
          $.ajax({
            url: "/people",
            type: "GET",
            success: function(data){
              if (!data)
                  alert("ERROR data");
              else {

                $("#list").empty();
               
                for (let i=0;i<data.length;i++) {
                   $("#list").append("<li>" + data[i].ident + " " + data[i].name + "</li>");
                }
                
              }
            },
            dataType: "json"
          });              
        } else {
          $.ajax({
            url: "/people/" + $("#ident").val(),
            type: "GET",
            success: function(data){
              if (!data)
                  alert("ERROR data");
              else
                  $("#name").val(data.name);        
            },
            dataType: "json"
          });   
        }
  		  return false;
  		}
 		
  		function createClicked(){
          if ($("#ident").val() == "") {
            alert("ERROR");
            return false;
          }

          $.ajax({
            url: "/people",
            type: "POST",
            data: {ident:Number($("#ident").val()), name:$("#name").val()},
            success: function(data){
              if (!data)
                alert("ERROR");
              else
                alert("CREATE VALID");
            } ,     
            dataType: "json"
          }); 
    		  return false;
    	}

      function updateClicked(){

          if ($("#ident").val() == "") {
            alert("ERROR");
            return false;
          }        
          $.ajax({
          url: "/people",
          type: "PUT",
          data: {ident:Number($("#ident").val()) , name:$("#name").val()},
          success: function(data){
              if (!data)
                alert("ERROR");
              else
                alert("UPDATE VALID");
            } ,     
          dataType: "json"
        });    
          return false;          
      }

      function deleteClicked(){
          $.ajax({
            url: "/people?ident="+ $("#ident").val() ,
            type: "DELETE",
            success: function(data) { 
              if (!data)
                alert("NO DELETE");
              else
                alert("GOOD DELETE");
            } ,   
            dataType: "json"
          });  

          return false;             
      }

  		$(document).ready(function(){ 

        $("#name").keydown( function( event ) {
            if ( event.which === 13 ) {
              createClicked();
              event.preventDefault();
              return false;
            }
        });
        
        $("#ident").keydown( function( event ) {
            if ( event.which === 13 ) {
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
    

