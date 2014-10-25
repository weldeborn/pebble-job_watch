var initialized = false;

Pebble.addEventListener("ready", function() {
  console.log("ready called!");
  initialized = true;
});

Pebble.addEventListener("showConfiguration", function() {
  console.log("showing configuration");
  Pebble.openURL('http://weldeborn.esy.es/configurable.html');
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  // webview closed
  var options = JSON.parse(decodeURIComponent(e.response));
  console.log("Options = " + JSON.stringify(options));
  Pebble.sendAppMessage({CFG_PROJECT_1:options["project_1"], 
	  					 CFG_PROJECT_2:options["project_2"], 
	  					 CFG_PROJECT_3:options["project_3"]});
});