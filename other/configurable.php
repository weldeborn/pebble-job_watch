<!DOCTYPE html>
<html>
  <head>
    <title>Configurable</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="http://code.jquery.com/mobile/1.3.2/jquery.mobile-1.3.2.min.css" />
    <script src="http://code.jquery.com/jquery-1.9.1.min.js"></script>
    <script src="http://code.jquery.com/mobile/1.3.2/jquery.mobile-1.3.2.min.js"></script>
  </head>
  <body>
    <div data-role="page" id="main">
      <div data-role="header" class="jqm-header">
        <h1>Configurable Pebble App</h1>
      </div>

      <div data-role="content">

        <div data-role="fieldcontain">
          <label for="CMD_CFG_PROJECT_1">Project 1:</label>
          <textarea cols="40" rows="8" name="CMD_CFG_PROJECT_1" id="CMD_CFG_PROJECT_1"><?php echo $_GET["CMD_CFG_PROJECT_1"]; ?></textarea>

          <label for="CMD_CFG_PROJECT_2">Project 2:</label>
          <textarea cols="40" rows="8" name="CMD_CFG_PROJECT_2" id="CMD_CFG_PROJECT_2"><?php echo $_GET["CMD_CFG_PROJECT_2"]; ?></textarea>

          <label for="CMD_CFG_PROJECT_3">Project 3:</label>
          <textarea cols="40" rows="8" name="CMD_CFG_PROJECT_3" id="CMD_CFG_PROJECT_3"><?php echo $_GET["CMD_CFG_PROJECT_3"]; ?></textarea>
        </div>

        <div data-role="fieldcontain">
          <fieldset data-role="controlgroup">
            <legend>Vibration alerts:</legend>
            <input type="checkbox" name="CMD_CFG_VIB_7_WORK" id="CMD_CFG_VIB_7_WORK" class="custom" />
            <label for="CMD_CFG_VIB_7_WORK">Vibrate 7min before bus/tram departure (From work, 16:00-18:00 )</label>

            <input type="checkbox" name="CMD_CFG_VIB_7_HOME" id="CMD_CFG_VIB_7_HOME" class="custom" />
            <label for="CMD_CFG_VIB_7_HOME">Vibrate 7min before bus/tram departure (From home, 07:00-09:00)</label>
          </fieldset>
          </div>
        </div>

        <div class="ui-body ui-body-b">
          <fieldset class="ui-grid-a">
              <div class="ui-block-a"><button type="submit" data-theme="d" id="b-cancel">Cancel</button></div>
              <div class="ui-block-b"><button type="submit" data-theme="a" id="b-submit">Submit</button></div>
            </fieldset>
          </div>
        </div>
      </div>
    </div>
    <script>
      
        $('#CMD_CFG_VIB_7_WORK').prop('checked', <?php echo $_GET["CMD_CFG_VIB_7_WORK"]; ?>);
        $('#CMD_CFG_VIB_7_HOME').prop('checked', <?php echo $_GET["CMD_CFG_VIB_7_HOME"]; ?>);


      function getQueryVariable(variable) {
        var query = window.location.search.substring(1);
        var vars = query.split("&");
        for (var i=0;i<vars.length;i++) {
          var pair = vars[i].split("=");
          if(pair[0] == variable) {
            return pair[1];
          }
        }
        return(false);
      }

      function saveOptions() {
        var options = {
          'CMD_CFG_PROJECT_1': $("#CMD_CFG_PROJECT_1").val(),
          'CMD_CFG_PROJECT_2': $("#CMD_CFG_PROJECT_2").val(),
          'CMD_CFG_PROJECT_3': $("#CMD_CFG_PROJECT_3").val(),
          'CMD_CFG_VIB_7_WORK': $("#CMD_CFG_VIB_7_WORK").is(':checked'),
          'CMD_CFG_VIB_7_HOME': $("#CMD_CFG_VIB_7_HOME").is(':checked'),
        }
        return options;
      }

      $().ready(function() {        
        $("#b-cancel").click(function() {
          console.log("Cancel");
          document.location = "pebblejs://close";
        });

        $("#b-submit").click(function() {
          console.log("Submit");

          var location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(saveOptions()));
          console.log("Warping to: " + location);
          console.log(location);
          document.location = location;
        });

      });
    </script>
  </body>
</html>
