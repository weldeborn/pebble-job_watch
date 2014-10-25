var initialized = false;
var config_url ="http://weldeborn.esy.es/configurable.php?v=0.1";

Pebble.addEventListener("ready", function() {
  console.log("ready called!");
  initialized = true;
});

Pebble.addEventListener("showConfiguration", function() {
  console.log("showing configuration");
  var url = config_url;
  for(var i = 0, x = window.localStorage.length; i < x; i++) {
	var key = window.localStorage.key(i);
	var val = window.localStorage.getItem(key);
	
	if(val != null) {
		url += "&" + encodeURIComponent(key) + "=" + encodeURIComponent(val);
	}
  }

  console.log(url);
  
  Pebble.openURL(url);
  
});


Pebble.addEventListener("webviewclosed", function(_event) {
	if(_event.response) {
		var values = JSON.parse(decodeURIComponent(_event.response));
		console.log(JSON.stringify(values));
		for(key in values) {
			window.localStorage.setItem(key, values[key]);
		}
		
		Pebble.sendAppMessage(values,
			function(_event) {
				console.log("Successfully sent options to Pebble");
			},
			function(_event) {
				console.log("Failed to send options to Pebble.\nError: " + _event.error.message);
			}
		);
	}
});

Pebble.addEventListener("appmessage",
        function(e) {
          console.log(e.payload.CMD_CFG_PROJECT_1);
          console.log("message received in javascript!");
        });