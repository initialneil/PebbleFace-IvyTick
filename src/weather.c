#include "weather.h"
#include "common.h"
#include "gpath-draw.h"

static Layer *s_weather_layer;
static GPoint s_center;
static int s_radius = 0, s_win_w = 0, s_win_h = 0;

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

  s_weather_layer = layer_create(GRect(0, s_win_h - 25, s_win_w, 25));
  layer_set_update_proc(s_weather_layer, update_weather_proc);
}

Layer * get_weather_layer() {
  return s_weather_layer;
}

static void update_weather_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "update weather layer");
    
  GPoint weather_origin = GPoint(s_win_w - 25, 0);
  
  draw_custom_weather_gpath(ctx, TIMELINE_WEATHER, weather_origin);
}

void release_weather_layer() {
  custom_weather_gpath_destroy();
}


















