#include "app_msg.h"
#include "weather.h"

// Store incoming information
static char temperature_buffer[8];
static char conditions_buffer[32];
static char city_buffer[32];

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case WEATHER_ICON_KEY:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      APP_LOG(APP_LOG_LEVEL_INFO, "weather condition = %s", conditions_buffer);
      break;
      
    case WEATHER_TEMPERATURE_KEY:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%d.C", (int)t->value->int32);
      APP_LOG(APP_LOG_LEVEL_INFO, "temperature = %s", temperature_buffer);
      break;
      
    case WEATHER_CITY_KEY:
      snprintf(city_buffer, sizeof(city_buffer), "%s", t->value->cstring);
      APP_LOG(APP_LOG_LEVEL_INFO, "city = %s", city_buffer);
      break;
      
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  
  // Update weather layer
  update_weather_layer(conditions_buffer, temperature_buffer, city_buffer);
}


