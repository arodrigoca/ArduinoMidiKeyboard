const char MAIN_page[] PROGMEM = R"=====(
	<!DOCTYPE html>
	<html>
	<head>
    <title>Sunvox Controller</title>
		<style>
			#main_header{
				color: blue;
			}

			button{
				background-color: #4CAF50; /* Green */
	  		border: none;
	  		color: white;
	  		padding: 15px 32px;
	  		text-align: center;
	  		text-decoration: none;
	  		display: inline-block;
	  		font-size: 24px;
				border-radius: 12px;
				border: 2px solid blue; /* Green */
				box-shadow: 0 9px #999;
				width: 100%;
				padding: 50px;
			}

			button:active{
				box-shadow: 0 5px #666;
	  		transform: translateY(4px);
			}
		</style>
	</head>
	<body>

	<div>
	<h1 id="main_header">Sunvox Controller</h1>
		<div>
			<button type="button" onclick="sendData('gen_up')">Generator Up</button>
		</div>
		<br>
		<div>
			<button type="button" onclick="sendData('gen_down')">Generator Down</button><BR>
		</div>
	</div>
	<br>
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
