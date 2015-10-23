#include "app_msg.h"
#include "weather.h"

// Store incoming information
static char temperature_buffer[8];
static char conditions_buffer[32];
static char city_buffer[32], default_location_buffer[32], location_opt_buffer[32];

static bool s_show_weather = true, s_show_location = true;

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Init current config
  get_weather_config(&s_show_weather, &s_show_location);
  
  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
      // PebbleKit JS Ready
      case PEBBLEKIT_JS_READY:
        set_pebblekit_js_ready((bool)t->value->int8);
        update_weather_with_app_msg();
        break;
      
      // Weather Info
      case WEATHER_ICON_KEY:
        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "weather condition = %s", conditions_buffer);
        set_conditions_buffer(conditions_buffer);
        break;
        
      case WEATHER_TEMPERATURE_KEY:
        snprintf(temperature_buffer, sizeof(temperature_buffer), "%d.C", (int)t->value->int32);
        APP_LOG(APP_LOG_LEVEL_INFO, "temperature = %s", temperature_buffer);
        set_temperature_buffer(temperature_buffer);
        break;
        
      case WEATHER_CITY_KEY:
        snprintf(city_buffer, sizeof(city_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "city = %s", city_buffer);
        set_city_buffer(city_buffer);
        break;
        
      // Display Weather & Location
      case SHOW_WEATHER:
        s_show_weather = t->value->int8;
        APP_LOG(APP_LOG_LEVEL_INFO, "show weather = %d", s_show_weather);
        break;
      
      case SHOW_LOCATION:
        s_show_location = t->value->int8;
        APP_LOG(APP_LOG_LEVEL_INFO, "show location = %d", s_show_location);
        break;
      
      case DEFAULT_LOCATION:
        snprintf(default_location_buffer, sizeof(city_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "default location = %s", default_location_buffer);
        set_default_location(default_location_buffer);
        break;
      
      case LOCATION_OPT:
        snprintf(location_opt_buffer, sizeof(city_buffer), "%s", t->value->cstring);
        APP_LOG(APP_LOG_LEVEL_INFO, "location opt = %s", location_opt_buffer);
        set_location_opt(location_opt_buffer);
        break;
        
      default:
        APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
        break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  
  // Update weather layer
  config_weather_layer(s_show_weather, s_show_location);
  refresh_weather_display();
}


