const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<div>
<h1>Sunvox Controller</h1>
	<button type="button" onclick="sendData(1)">Generator Up</button>
	<button type="button" onclick="sendData(0)">Generator Down</button><BR>
</div>

<div>
    <span id="last_command">NA</span>
</div>
<script>
function sendData(command) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("last_command").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "send_command?command="+command, true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";
