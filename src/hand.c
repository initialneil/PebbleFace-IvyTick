#include "hand.h"
#include "common.h"

static Layer *s_hand_layer;
static GPoint s_center;
static int s_radius = 0, s_win_w = 0, s_win_h = 0;

static Time s_cur_time;

Layer * init_hand_layer(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init hand layer");
  
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  s_center = grect_center_point(&window_bounds);
  
  s_win_w = window_bounds.size.w;
  s_win_h = window_bounds.size.h;
  
  s_radius = s_win_w < s_win_h ? s_win_w : s_win_h;
  s_radius /= 2;
  s_radius -= 2;

  s_hand_layer = layer_create(window_bounds);
  layer_set_update_proc(s_hand_layer, update_hand_proc);
  
  return s_hand_layer;
}

static void draw_hand_from_center(GContext *ctx, GPoint dot, float s0, float s1, GColor color0, int16_t width) {  
  GPoint dot_0 = s_center;
  dot_0.x += (dot.x - s_center.x) * s0;
  dot_0.y += (dot.y - s_center.y) * s0;
  
  GPoint dot_1 = s_center;
  dot_1.x += (dot.x - s_center.x) * s1;
  dot_1.y += (dot.y - s_center.y) * s1;
  
  graphics_context_set_stroke_color(ctx, color0);
  graphics_context_set_stroke_width(ctx, width);
  graphics_draw_line(ctx, dot_0, dot_1);
}

static void update_hand_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "update hand layer");
  
  GPoint dot_, dot_0, dot_1;
  
  // calc minute hand
  graphics_context_set_antialiased(ctx, true);

  float minute_angle = TRIG_MAX_ANGLE * s_cur_time.minutes / 60;
  GPoint minutes_dot = (GPoint) {
    .x = (int16_t)(sin_lookup(minute_angle) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.x,
    .y = (int16_t)(-cos_lookup(minute_angle) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.y,
  };
  
  // calc hour hand
  float hour_angle = TRIG_MAX_ANGLE * s_cur_time.hours / 12;
  hour_angle += (minute_angle / TRIG_MAX_ANGLE) * (TRIG_MAX_ANGLE / 12);
  GPoint hours_dot = (GPoint) {
    .x = (int16_t)(sin_lookup(hour_angle) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.x,
    .y = (int16_t)(-cos_lookup(hour_angle) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.y,
  };
  
  // draw hour hand and minute hand
  draw_hand_from_center(ctx, hours_dot, 0, 0.6, HOUR_HAND_COLOR, 20);
  draw_hand_from_center(ctx, minutes_dot, -0.2, 0.95, MINUTE_HAND_COLOR, 2);
  
  // Draw center dot
  graphics_context_set_antialiased(ctx, false);
  //graphics_context_set_fill_color(ctx, CENTER_DOT_COLOR);
  //graphics_fill_circle(ctx, s_center, 4);
  graphics_context_set_fill_color(ctx, CENTER_DOT_IN_COLOR);
  graphics_fill_circle(ctx, s_center, 2);
  
  // Plot Second Hand
  if (s_cur_time.seconds >= 0) {
    GPoint seconds_dot = (GPoint) {
      .x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * s_cur_time.seconds / 60) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.x,
      .y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * s_cur_time.seconds / 60) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.y,
    };
    
    dot_0 = s_center;
    dot_0.x += (seconds_dot.x - s_center.x);
    dot_0.y += (seconds_dot.y - s_center.y);
    
    dot_1 = s_center;
    dot_1.x -= (seconds_dot.x - s_center.x) * 0.2;
    dot_1.y -= (seconds_dot.y - s_center.y) * 0.2;
    
    graphics_context_set_stroke_color(ctx, SECOND_HAND_COLOR);
    graphics_context_set_stroke_width(ctx, 2);
    graphics_draw_line(ctx, dot_0, dot_1);
    
    // second hand certer dot
    graphics_context_set_fill_color(ctx, SECOND_HAND_COLOR);
    graphics_fill_circle(ctx, s_center, 3);
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_circle(ctx, s_center, 1);
  }
}

void set_hand_cur_time(struct tm *tick_time, bool SHOW_SECOND) {
  s_cur_time.hours = tick_time->tm_hour;
  s_cur_time.hours = s_cur_time.hours > 12 ? s_cur_time.hours - 12 : s_cur_time.hours;
  s_cur_time.minutes = tick_time->tm_min;
  
  // show second or not
  if (SHOW_SECOND)
    s_cur_time.seconds = tick_time->tm_sec;
  else
    s_cur_time.seconds = -1;
  
#ifdef SHOW_SCREENSHOT
  s_cur_time.hours = 10;
  s_cur_time.minutes = 10;
  s_cur_time.seconds = -1;
#endif

  // Redraw
  if(s_hand_layer) {
    layer_mark_dirty(s_hand_layer);
  }
}
















