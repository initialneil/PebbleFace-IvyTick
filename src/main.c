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

static bool s_show_weather = true, s_show_location = true;

/************************************ UI **************************************/
static void hand_tick_handler(struct tm *tick_time, TimeUnits changed) {
  // update hand
  set_hand_cur_time(tick_time, SHOW_SECOND);
  
  // update date
  set_date_layer_cur_time(tick_time);
  
  // update weather
  config_weather_layer(s_show_weather, s_show_location);
  update_weather_with_app_msg(tick_time);
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
  if (persist_exists(SHOW_WEATHER))
    s_show_weather = persist_read_bool(SHOW_WEATHER);
  
  if (persist_exists(SHOW_LOCATION))
    s_show_location = persist_read_bool(SHOW_LOCATION);
}

/*********************************** App **************************************/
static void init() {
  srand(time(NULL));
  
  // init configuration
  init_config();

  // init main window
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_main_window, true);

  // handle tick now
  time_t t = time(NULL);
  struct tm *time_now = localtime(&t);
  hand_tick_handler(time_now, SHOW_SECOND);
  
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
