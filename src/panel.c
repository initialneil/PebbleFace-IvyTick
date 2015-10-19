#include "panel.h"
#include "common.h"

static Layer *s_panel_layer;
static GPoint s_center;
const int HOUR_BAR_MARGIN = 0;
static int s_radius = 0, s_win_w = 0, s_win_h = 0;

Layer * init_panel_layer(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init panel layer");
  
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  s_center = grect_center_point(&window_bounds);
  APP_LOG(APP_LOG_LEVEL_INFO, "window center: %d, %d", s_center.x, s_center.y);
  
  s_win_w = window_bounds.size.w;
  s_win_h = window_bounds.size.h;
  APP_LOG(APP_LOG_LEVEL_INFO, "window size: %d, %d", s_win_w, s_win_h);
  
  s_radius = s_win_w < s_win_h ? s_win_w : s_win_h;
  s_radius /= 2;
  s_radius -= 2;

  s_panel_layer = layer_create(window_bounds);
  layer_set_update_proc(s_panel_layer, update_panel_proc);
  
  return s_panel_layer;
}

static void update_panel_proc(Layer *layer, GContext *ctx) {
  APP_LOG(APP_LOG_LEVEL_INFO, "update panel layer");
  
  // Color background
  GRect bounds = layer_get_bounds(layer);

  graphics_context_set_fill_color(ctx, PANEL_OUT_COLOR);
  graphics_fill_rect(ctx, bounds, 0, GCornerNone);
  
  graphics_context_set_fill_color(ctx, PANEL_IN_COLOR);
  graphics_fill_circle(ctx, s_center, s_radius + 1);
  
  // Plot Dots
  graphics_context_set_antialiased(ctx, true);
  
  for (int i = 0; i < 60; i++) {
    // hour bar
    if (i % 5 == 0 && i / 5 != -1) {
      GPoint dot = (GPoint) {
        .x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius - HOUR_BAR_MARGIN) / TRIG_MAX_RATIO) + s_center.x,
        .y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius - HOUR_BAR_MARGIN) / TRIG_MAX_RATIO) + s_center.y,
      };
      
      GPoint dot_start = dot;
      dot_start.x += (s_center.x - dot.x) * 0.1;
      dot_start.y += (s_center.y - dot.y) * 0.1;
      
      graphics_context_set_stroke_color(ctx, HOUR_DOTS_COLOR);
      
      // emphasis
      if (i % 15 == 0)
        graphics_context_set_stroke_color(ctx, GColorWhite);
      
      graphics_context_set_stroke_width(ctx, 2);
      graphics_draw_line(ctx, dot_start, dot);
    }
    
    // minute dots
    if (i % 5 == 0) {
      graphics_context_set_stroke_color(ctx, HOUR_DOTS_COLOR);
      
      // emphasis
      if (i % 15 == 0)
        graphics_context_set_stroke_color(ctx, GColorWhite);
    } else {
      graphics_context_set_stroke_color(ctx, MINUTE_DOTS_COLOR);
    }
    
    GPoint dot = (GPoint) {
      .x = (int16_t)(sin_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.x,
      .y = (int16_t)(-cos_lookup(TRIG_MAX_ANGLE * i / 60) * (int32_t)(s_radius) / TRIG_MAX_RATIO) + s_center.y,
    };

    GPoint dot_;
    for (int x = -1; x <= 1; x++) {
      for (int y = -1; y <= 1; y++) {
        dot_ = dot;
        dot_.x += x;
        dot_.y += y;
        graphics_draw_pixel(ctx, dot_);
      }
    }
  }
}














