// Got from OpenWeatherMap's API example
var myAPIKey = 'bd82977b86bf27fb59a04b61b657fb6f';

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
    
    // Get the initial weather
    getWeather();
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('AppMessage received!');
    
    // Get the weather if required
    getWeather();
  }                     
);

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

function locationSuccess(pos) {
  var coordinates = pos.coords;
  console.log("latitude = " + coordinates.latitude, "longitude = " + coordinates.longitude);
  fetchWeather(coordinates.latitude, coordinates.longitude);  
}

function locationError(err) {
  console.log('Error requesting location!');
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}
