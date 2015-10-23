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
static bool s_show_weather = true, s_show_location = true;
static char *s_default_location, *s_location_opt;

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

  s_weather_layer = layer_create(GRect(s_win_w - 26, s_win_h - 28, 25, 25));
  layer_set_update_proc(s_weather_layer, update_weather_proc);
  
  // set font
  s_text_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DIGITAL_16));
  
  // create temperature TextLayer
  //s_temperature_layer = text_layer_create(GRect(s_win_w - 48, s_win_h - 18, 30, 18));
  s_temperature_layer = text_layer_create(GRect(1, s_win_h - 20, 30, 18));
  text_layer_set_text_color(s_temperature_layer, TEMPERATURE_COLOR);
  text_layer_set_background_color(s_temperature_layer, GColorClear);
  text_layer_set_text_alignment(s_temperature_layer, GTextAlignmentLeft);
  text_layer_set_font(s_temperature_layer, s_text_font);
  
  // create city TextLayer
  s_city_layer = text_layer_create(GRect(22, s_win_h - 55, s_win_w - 44, 18));
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

void config_weather_layer(bool show_weather, bool show_location) {
  s_show_weather = show_weather;
  s_show_location = show_location;
  
  layer_set_hidden(s_weather_layer, !show_weather);
  layer_set_hidden(text_layer_get_layer(s_temperature_layer), !show_weather);
  layer_set_hidden(text_layer_get_layer(s_city_layer), !show_location);
  
  persist_write_bool(SHOW_WEATHER, s_show_weather);
  persist_write_bool(SHOW_LOCATION, s_show_location);
}

void get_weather_config(bool *show_weather, bool *show_location) {
  *show_weather = s_show_weather;
  *show_location = s_show_location;
}

void config_location_setting(char *default_location, char *location_opt) {
  s_default_location = default_location;
  s_location_opt = location_opt;
}

void set_default_location(const char default_location[]) {
  strcpy(s_default_location, default_location);
  persist_write_string(DEFAULT_LOCATION, default_location);
}

void set_location_opt(const char location_opt[]) {
  strcpy(s_location_opt, location_opt);
  persist_write_string(LOCATION_OPT, location_opt);
}

void set_conditions_buffer(const char conditions_buffer[]) {
  strcpy(s_conditions_buffer, conditions_buffer);
  persist_write_string(WEATHER_ICON_KEY, conditions_buffer);
}

void set_temperature_buffer(const char temperature_buffer[]) {
  strcpy(s_temperature_buffer, temperature_buffer);
  persist_write_string(WEATHER_TEMPERATURE_KEY, temperature_buffer);
}

void set_city_buffer(const char city_buffer[]) {
  strcpy(s_city_buffer, city_buffer);
  persist_write_string(WEATHER_CITY_KEY, city_buffer);
}

static void update_weather_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "update weather layer");
    
  GPoint weather_origin = GPoint(0, 0);
  draw_custom_weather_gpath(ctx, WEATHER_GPATH_ID, weather_origin);
}

void refresh_weather_display() {
  if (strcmp(s_conditions_buffer, "Thunderstorm") == 0) {
    WEATHER_GPATH_ID = HEAVY_RAIN;
  } else if (strcmp(s_conditions_buffer, "Drizzle") == 0) {
    WEATHER_GPATH_ID = LIGHT_RAIN;
  } else if (strcmp(s_conditions_buffer, "Rain") == 0) {
    WEATHER_GPATH_ID = LIGHT_RAIN;
  } else if (strcmp(s_conditions_buffer, "Snow") == 0) {
    WEATHER_GPATH_ID = LIGHT_SNOW;
  } else if (strcmp(s_conditions_buffer, "Atmosphere") == 0) {
    WEATHER_GPATH_ID = CLOUDY_DAY;
  } else if (strcmp(s_conditions_buffer, "Clear") == 0) {
    WEATHER_GPATH_ID = TIMELINE_SUN;
  } else if (strcmp(s_conditions_buffer, "Clouds") == 0) {
    WEATHER_GPATH_ID = PARTLY_CLOUDY;
  } else if (strcmp(s_conditions_buffer, "Extreme") == 0) {
    WEATHER_GPATH_ID = TIMELINE_WEATHER;
  } else if (strcmp(s_conditions_buffer, "Additional") == 0) {
    WEATHER_GPATH_ID = TIMELINE_WEATHER;
  } else {
    WEATHER_GPATH_ID = WEATHER_UNKNOWN;
  }
  
  text_layer_set_text(s_temperature_layer, s_temperature_buffer);
  text_layer_set_text(s_city_layer, s_city_buffer);
  
  // Redraw
  if(s_weather_layer) {
    layer_mark_dirty(s_weather_layer);
  }
}

void config_weather_buffer(char *conditions_buffer, char *temperature_buffer, char *city_buffer) {
  s_conditions_buffer = conditions_buffer;
  s_temperature_buffer = temperature_buffer;
  s_city_buffer = city_buffer;
}

void update_weather_with_app_msg() {
  // Get weather update every 30 minutes
  APP_LOG(APP_LOG_LEVEL_INFO, "weather update with js");

  // Begin dictionary
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);

  // Add a key-value pair
  dict_write_cstring(iter, DEFAULT_LOCATION, s_default_location);
  dict_write_cstring(iter, LOCATION_OPT, s_location_opt);

  // Send the message!
  app_message_outbox_send();
}

void release_weather_layer() {
  custom_weather_gpath_destroy();
  fonts_unload_custom_font(s_text_font);
}


















