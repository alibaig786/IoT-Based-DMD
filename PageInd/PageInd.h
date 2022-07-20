const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      html {
        font-family: Arial;
        display: inline-block;
        margin: 0px auto;
        text-align: center;
      }

      h1 { font-size: 2.0rem; color:#2980b9;}
      
      .buttonSend {
        display: inline-block;
        padding: 15px 25px;
        font-size: 24px;
        font-weight: bold;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #4CAF50;
        border: none;
        border-radius: 15px;
        box-shadow: 0 5px #999;
      }
        .buttonSend:hover {background-color: #3e8e41}
        .buttonSend:active {
        background-color: #3e8e41;
        box-shadow: 0 1px #666;
        transform: translateY(4px);
      }
    </style>
  </head>
  
  <body>
    <div>
      <h1>IoT BASE DMD CONTROL</h1>
      <h2>ENTER TEXT :</h2><br>
      <textarea id="TextBox" name="TextBox" rows="4" cols="50"></textarea>
      <br><br>
      </div>
      <br>
      
      
    <div>
      <button type="button" class="buttonSend" onclick="sendData()">Send</button>
    </div>

    <script>
      function sendData() {
        var Text = document.getElementById("TextBox").value;
        var xhttp = new XMLHttpRequest();
        xhttp.open("GET", "setText?TextContents="+Text, true);
        xhttp.send(); 
      }
    </script>
  </body>
</html>
)=====";
