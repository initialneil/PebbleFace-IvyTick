#include <pebble.h>
#include "common.h"
#include "panel.h"
#include "hand.h"
#include "text.h"

#define ANTIALIASING true

#define HAND_MARGIN  10
#define FINAL_RADIUS 55

#define ANIMATION_DURATION 500
#define ANIMATION_DELAY    600

const bool SHOW_SECOND = false;

static Window *s_main_window;
static Layer *s_panel_layer, *s_hand_layer;
static TextLayer *s_month_layer, *s_date_layer, *s_weekday_layer;

/************************************ UI **************************************/
static void hand_tick_handler(struct tm *tick_time, TimeUnits changed) {
  // update hand
  set_hand_cur_time(tick_time, SHOW_SECOND);
  
  // update date
  set_date_layer_cur_time(tick_time);
}

static void window_load(Window *window) {
  // init layers
  s_panel_layer = init_panel_layer(window);
  s_hand_layer = init_hand_layer(window);
  init_date_layer(window);
  s_month_layer = get_month_layer();
  s_date_layer = get_date_layer();
  s_weekday_layer = get_weekday_layer();
  
  // add to window layer
  Layer *window_layer = window_get_root_layer(window);
  layer_add_child(window_layer, s_panel_layer);

  layer_add_child(window_layer, text_layer_get_layer(s_month_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
  layer_add_child(window_layer, text_layer_get_layer(s_weekday_layer));

  layer_add_child(window_layer, s_hand_layer);
}

static void window_unload(Window *window) {
  layer_destroy(s_panel_layer);
  layer_destroy(s_hand_layer);
  text_layer_destroy(s_month_layer);
  text_layer_destroy(s_date_layer);
  text_layer_destroy(s_weekday_layer);
  release_date_layer();
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

  // handle tick now
  time_t t = time(NULL);
  struct tm *time_now = localtime(&t);
  hand_tick_handler(time_now, SHOW_SECOND);
  
  // subscribe on time tick
  tick_timer_service_subscribe(SECOND_UNIT, hand_tick_handler);
}

static void deinit() {
  window_destroy(s_main_window);
}

int main() {
  init();
  app_event_loop();
  deinit();
}
