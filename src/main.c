#include <pebble.h>
#include "common.h"
#include "panel.h"
#include "hand.h"
#include "text.h"
#include "weather.h"
#include "app_msg.h"

#define ANTIALIASING true

#define HAND_MARGIN  10
#define FINAL_RADIUS 55

#define ANIMATION_DURATION 500
#define ANIMATION_DELAY    600

const bool SHOW_SECOND = false;

static Window *s_main_window;
static Layer *s_panel_layer, *s_hand_layer, *s_weather_layer;
static TextLayer *s_month_layer, *s_date_layer, *s_weekday_layer;
static TextLayer *s_temperature_layer, *s_city_layer;

static char s_conditions_buffer[32], s_temperature_buffer[32], s_city_buffer[32];
static bool s_show_weather = true, s_show_location = true;
static char s_default_location[32], s_location_opt[32];

/************************************ UI **************************************/
static void hand_tick_handler(struct tm *tick_time, TimeUnits changed) {
  // update hand
  set_hand_cur_time(tick_time, SHOW_SECOND);
  
  // update date
  set_date_layer_cur_time(tick_time);
  
  // update weather
  if (tick_time->tm_min % 30 == 0)
    update_weather_with_app_msg();
}

static void window_load(Window *window) {
  // init layers
  s_panel_layer = init_panel_layer(window);
  s_hand_layer = init_hand_layer(window);
  
  init_date_layer(window);
  s_month_layer = get_month_layer();
  s_date_layer = get_date_layer();
  s_weekday_layer = get_weekday_layer();
  
  init_weather_layer(window);
  s_weather_layer = get_weather_layer();
  s_temperature_layer = get_temperature_layer();
  s_city_layer = get_city_layer();
  
  // add to window layer
  Layer *window_layer = window_get_root_layer(window);
  layer_add_child(window_layer, s_panel_layer);

  layer_add_child(window_layer, text_layer_get_layer(s_month_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_weekday_layer));

  layer_add_child(window_layer, s_weather_layer);
  layer_add_child(window_layer, text_layer_get_layer(s_temperature_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_city_layer));
  
  layer_add_child(window_layer, s_hand_layer);
}

static void window_unload(Window *window) {
  layer_destroy(s_panel_layer);
  layer_destroy(s_hand_layer);
  
  text_layer_destroy(s_month_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_weekday_layer);
  release_date_layer();
  
  layer_destroy(s_weather_layer);
  text_layer_destroy(s_temperature_layer);
  text_layer_destroy(s_city_layer);
  release_weather_layer();
}

static void init_config() {
  // display
  if (persist_exists(SHOW_WEATHER))
    s_show_weather = persist_read_bool(SHOW_WEATHER);
  
  if (persist_exists(SHOW_LOCATION))
    s_show_location = persist_read_bool(SHOW_LOCATION);
  
  config_weather_layer(s_show_weather, s_show_location);
  
  // weather & location diaplay
  memset(s_conditions_buffer, 0, sizeof(s_conditions_buffer));
  if (persist_exists(WEATHER_ICON_KEY))
    persist_read_string(WEATHER_ICON_KEY, s_conditions_buffer, sizeof(s_conditions_buffer));
  
  memset(s_temperature_buffer, 0, sizeof(s_temperature_buffer));
  if (persist_exists(WEATHER_TEMPERATURE_KEY))
    persist_read_string(WEATHER_TEMPERATURE_KEY, s_temperature_buffer, sizeof(s_temperature_buffer));
  
  memset(s_city_buffer, 0, sizeof(s_city_buffer));
  if (persist_exists(WEATHER_CITY_KEY))
    persist_read_string(WEATHER_CITY_KEY, s_city_buffer, sizeof(s_city_buffer));
  
  config_weather_buffer(s_conditions_buffer, s_temperature_buffer, s_city_buffer);
  
  // location setting
  memset(s_default_location, 0, sizeof(s_default_location));
  if (persist_exists(DEFAULT_LOCATION))
    persist_read_string(DEFAULT_LOCATION, s_default_location, sizeof(s_default_location));
  
  memset(s_location_opt, 0, sizeof(s_location_opt));
  if (persist_exists(LOCATION_OPT))
    persist_read_string(LOCATION_OPT, s_location_opt, sizeof(s_location_opt));
  
  config_location_setting(s_default_location, s_location_opt);
}

/*********************************** App **************************************/
static void init() {
  srand(time(NULL));

  // init main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);
  
  // init configuration
  init_config();

  // handle tick now
  time_t t = time(NULL);
  struct tm *time_now = localtime(&t);
  hand_tick_handler(time_now, 0);
  refresh_weather_display();
  
  // subscribe on time tick
  if (SHOW_SECOND)
    tick_timer_service_subscribe(SECOND_UNIT, hand_tick_handler);
  else
    tick_timer_service_subscribe(MINUTE_UNIT, hand_tick_handler);
  
  // register app message callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // open AppMessage
  APP_LOG(APP_LOG_LEVEL_INFO, "inbox: %d, outbox: %d", 
          APP_MESSAGE_INBOX_SIZE_MINIMUM, APP_MESSAGE_OUTBOX_SIZE_MINIMUM);
  app_message_open(APP_MESSAGE_INBOX_SIZE_MINIMUM, APP_MESSAGE_OUTBOX_SIZE_MINIMUM);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
