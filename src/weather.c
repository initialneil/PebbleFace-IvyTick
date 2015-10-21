#include "weather.h"
#include "common.h"
#include "gpath_draw.h"

static Layer *s_weather_layer;
static TextLayer *s_temperature_layer, *s_city_layer;
static GFont s_text_font;

static GPoint s_center;
static int s_radius = 0, s_win_w = 0, s_win_h = 0;

static int WEATHER_GPATH_ID = WEATHER_UNKNOWN;
static char *s_conditions_buffer, *s_temperature_buffer, *s_city_buffer;

void init_weather_layer(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init weather layer");
  
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  s_center = grect_center_point(&window_bounds);
  
  s_win_w = window_bounds.size.w;
  s_win_h = window_bounds.size.h;
  
  s_radius = s_win_w < s_win_h ? s_win_w : s_win_h;
  s_radius /= 2;
  s_radius -= 2;

  s_weather_layer = layer_create(GRect(s_win_w - 26, s_win_h - 26, 26, 26));
  layer_set_update_proc(s_weather_layer, update_weather_proc);
  
  // set font
  s_text_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DIGITAL_16));
  
  // create temperature TextLayer
  //s_temperature_layer = text_layer_create(GRect(s_win_w - 48, s_win_h - 18, 30, 18));
  s_temperature_layer = text_layer_create(GRect(2, s_win_h - 18, 30, 18));
  text_layer_set_text_color(s_temperature_layer, TEMPERATURE_COLOR);
  text_layer_set_background_color(s_temperature_layer, GColorClear);
  text_layer_set_text_alignment(s_temperature_layer, GTextAlignmentLeft);
  text_layer_set_font(s_temperature_layer, s_text_font);
  
  // create city TextLayer
  s_city_layer = text_layer_create(GRect(20, s_win_h - 55, s_win_w - 40, 18));
  text_layer_set_text_color(s_city_layer, CITY_COLOR);
  text_layer_set_background_color(s_city_layer, GColorClear);
  text_layer_set_text_alignment(s_city_layer, GTextAlignmentCenter);
  text_layer_set_font(s_city_layer, s_text_font);
}

Layer * get_weather_layer() {
  return s_weather_layer;
}

TextLayer * get_temperature_layer() {
  return s_temperature_layer;
}

TextLayer * get_city_layer() {
  return s_city_layer;
}

static void update_weather_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "update weather layer");
    
  GPoint weather_origin = GPoint(0, 0);
  draw_custom_weather_gpath(ctx, WEATHER_GPATH_ID, weather_origin);
}

void update_weather_layer(char *conditions_buffer, char *temperature_buffer, char *city_buffer) {
  s_conditions_buffer = conditions_buffer;
  s_temperature_buffer = temperature_buffer;
  s_city_buffer = city_buffer;
  
  if (strcmp(conditions_buffer, "Thunderstorm") == 0) {
    WEATHER_GPATH_ID = HEAVY_RAIN;
  } else if (strcmp(conditions_buffer, "Drizzle") == 0) {
    WEATHER_GPATH_ID = LIGHT_RAIN;
  } else if (strcmp(conditions_buffer, "Rain") == 0) {
    WEATHER_GPATH_ID = LIGHT_RAIN;
  } else if (strcmp(conditions_buffer, "Snow") == 0) {
    WEATHER_GPATH_ID = LIGHT_SNOW;
  } else if (strcmp(conditions_buffer, "Atmosphere") == 0) {
    WEATHER_GPATH_ID = CLOUDY_DAY;
  } else if (strcmp(conditions_buffer, "Clear") == 0) {
    WEATHER_GPATH_ID = TIMELINE_SUN;
  } else if (strcmp(conditions_buffer, "Clouds") == 0) {
    WEATHER_GPATH_ID = PARTLY_CLOUDY;
  } else if (strcmp(conditions_buffer, "Extreme") == 0) {
    WEATHER_GPATH_ID = TIMELINE_WEATHER;
  } else if (strcmp(conditions_buffer, "Additional") == 0) {
    WEATHER_GPATH_ID = TIMELINE_WEATHER;
  } else {
    WEATHER_GPATH_ID = WEATHER_UNKNOWN;
  }
  
  text_layer_set_text(s_temperature_layer, temperature_buffer);
  text_layer_set_text(s_city_layer, city_buffer);
  
  // Redraw
  if(s_weather_layer) {
    layer_mark_dirty(s_weather_layer);
  }
}

void update_weather_with_app_msg(struct tm *tick_time) {
  // Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
  
    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);
  
    // Send the message!
    app_message_outbox_send();
  }
}

void release_weather_layer() {
  custom_weather_gpath_destroy();
  fonts_unload_custom_font(s_text_font);
}


















