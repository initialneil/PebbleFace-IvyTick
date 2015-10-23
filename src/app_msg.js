// Got from OpenWeatherMap's API example
var myAPIKey = 'bd82977b86bf27fb59a04b61b657fb6f';
var show_weather, show_location;
var default_location = "", location_opt = "";

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    var dict = {
      'PEBBLEKIT_JS_READY': true,
    };
  
    // Send to watchapp
    Pebble.sendAppMessage(dict, function() {
      console.log('Send successful: ' + JSON.stringify(dict));
    }, function() {
      console.log('Send failed!');
    });
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Received message: ' + JSON.stringify(e.payload));
    
    default_location = e.payload.DEFAULT_LOCATION;
    location_opt = e.payload.LOCATION_OPT;
    console.log("default_location = " + default_location);
    console.log("location_opt = " + location_opt);
    
    // Get the weather if required
    refresh_weather();
  }                     
);

// Show Configure
Pebble.addEventListener('showConfiguration', function() {
  var url = 'http://initialneil.github.io/PebbleFace-IvyTick';
  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

// Configure Received
Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration page returned: ' + JSON.stringify(configData));

  show_weather = configData.show_weather;
  show_location = configData.show_location;
  default_location = configData.default_location;
  location_opt = configData.location_opt;
  console.log("show_weather = " + show_weather);
  console.log("show_location = " + show_location);
  console.log("default_location = " + default_location);
  console.log("location_opt = " + location_opt);

  var dict = {
    'SHOW_WEATHER': show_weather,
    'SHOW_LOCATION': show_location,
    'DEFAULT_LOCATION': default_location,
    'LOCATION_OPT': location_opt,
  };

  // Send to watchapp
  Pebble.sendAppMessage(dict, function() {
    console.log('Send successful: ' + JSON.stringify(dict));
  }, function() {
    console.log('Send failed!');
  });
  
  // Refresh weather
  if (show_weather || show_location)
    refresh_weather();
});

// Check weather id
function iconFromWeatherId(weatherId) {
  if (weatherId >= 200 && weatherId < 300) {
    return 'Thunderstorm';
  } else if (weatherId >= 300 && weatherId < 400) {
    return 'Drizzle';
  } else if (weatherId >= 500 && weatherId < 600) {
    return 'Rain';
  } else if (weatherId >= 600 && weatherId < 700) {
    return 'Snow';
  } else if (weatherId >= 700 && weatherId < 800) {
    return 'Atmosphere';
  } else if (weatherId == 800) {
    return 'Clear';
  } else if (weatherId > 800 && weatherId < 900) {
    return 'Clouds';
  } else if (weatherId >= 900 && weatherId < 910) {
    return 'Extreme';
  } else {
    return 'Additional';
  }
}

// Fetch weather from OpenWeatherMap with latitude and longitude
function fetchWeather(latitude, longitude) {
  var req = new XMLHttpRequest();
  req.open('GET', 'http://api.openweathermap.org/data/2.5/weather?' +
    'lat=' + latitude + '&lon=' + longitude + '&cnt=1&appid=' + myAPIKey, true);
  console.log('http://api.openweathermap.org/data/2.5/weather?' +
    'lat=' + latitude + '&lon=' + longitude + '&cnt=1&appid=' + myAPIKey);
  req.onload = function () {
    if (req.readyState === 4) {
      if (req.status === 200) {
        console.log(req.responseText);
        var response = JSON.parse(req.responseText);
        var temperature = Math.round(response.main.temp - 273.15);
        var icon = iconFromWeatherId(response.weather[0].id);
        var city = response.name;
        console.log(temperature);
        console.log(icon);
        console.log(city);
        Pebble.sendAppMessage({
          'WEATHER_ICON_KEY': icon,
          //'WEATHER_TEMPERATURE_KEY': temperature + '\xB0C',
          'WEATHER_TEMPERATURE_KEY': temperature,
          'WEATHER_CITY_KEY': city
        });
      } else {
        console.log('Error');
      }
    }
  };
  req.send(null);
}

// Fetch weather from OpenWeatherMap with city
function fetchWeather_city(city) {
  var req = new XMLHttpRequest();
  req.open('GET', 'http://api.openweathermap.org/data/2.5/weather?' +
    'q=' + city + '&cnt=1&appid=' + myAPIKey, true);
  console.log('http://api.openweathermap.org/data/2.5/weather?' +
    'q=' + city + '&cnt=1&appid=' + myAPIKey);
  req.onload = function () {
    if (req.readyState === 4) {
      if (req.status === 200) {
        console.log(req.responseText);
        var response = JSON.parse(req.responseText);
        var temperature = Math.round(response.main.temp - 273.15);
        var icon = iconFromWeatherId(response.weather[0].id);
        //var city = response.name;
        console.log(temperature);
        console.log(icon);
        console.log(city);
        Pebble.sendAppMessage({
          'WEATHER_ICON_KEY': icon,
          //'WEATHER_TEMPERATURE_KEY': temperature + '\xB0C',
          'WEATHER_TEMPERATURE_KEY': temperature,
          'WEATHER_CITY_KEY': city
        });
      } else {
        console.log('Error');
      }
    }
  };
  req.send(null);
}

function locationSuccess(pos) {
  var coordinates = pos.coords;
  console.log("latitude = " + coordinates.latitude, "longitude = " + coordinates.longitude);
  fetchWeather(coordinates.latitude, coordinates.longitude);  
}

function locationError(err) {
  console.log('Error requesting location!');
  
  console.log('Getting default city: ' + default_location);
  fetchWeather_city(default_location);
}

function getWeather_auto() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

function refresh_weather() {
  if (location_opt == "Default Only") {
    fetchWeather_city(default_location);
  } else {
    getWeather_auto();
  }
}
