#include "text.h"
#include "common.h"
#include <ctype.h>

static TextLayer *s_month_layer, *s_date_layer, *s_weekday_layer;
static GPoint s_center;
static int s_radius = 0, s_win_w = 0, s_win_h = 0;

static bool s_date_inited;
static Time s_cur_time;
static char month_buffer[16], date_buffer[16], weekday_buffer[16];
//static GFont s_month_font, s_date_font, s_weekday_font;
static GFont s_text_font;

void init_date_layer(Window *window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "init date layer");
  
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  s_center = grect_center_point(&window_bounds);
  
  s_win_w = window_bounds.size.w;
  s_win_h = window_bounds.size.h;
  
  s_radius = s_win_w < s_win_h ? s_win_w : s_win_h;
  s_radius /= 2;
  s_radius -= 2;

  // font
  // - fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_LIGHT_16))
  // - fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD)
  s_text_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_DIGITAL_16));

  // Create month TextLayer
  s_month_layer = text_layer_create(GRect(s_win_w - 39, 0, 40, 25));
  text_layer_set_text_color(s_month_layer, MONTH_COLOR);
  text_layer_set_background_color(s_month_layer, MONTH_BACKGROUND_COLOR);
  text_layer_set_text_alignment(s_month_layer, GTextAlignmentLeft);
  text_layer_set_font(s_month_layer, s_text_font);
  
  // Create date TextLayer
  s_date_layer = text_layer_create(GRect(s_win_w - 17, 0, 15, 25));
  text_layer_set_text_color(s_date_layer, DATE_COLOR);
  text_layer_set_background_color(s_date_layer, DATE_BACKGROUND_COLOR);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentRight);
  text_layer_set_font(s_date_layer, s_text_font);
  
  // Create Weekday TextLayer
  s_weekday_layer = text_layer_create(GRect(2, 0, 50, 20));
  text_layer_set_text_color(s_weekday_layer, WEEKDAY_COLOR);
  text_layer_set_background_color(s_weekday_layer, WEEKDAY_BACKGROUND_COLOR);
  text_layer_set_text_alignment(s_weekday_layer, GTextAlignmentLeft);
  text_layer_set_font(s_weekday_layer, s_text_font);
  
  s_date_inited = false;
}

TextLayer * get_month_layer() {
  return s_month_layer;
}

TextLayer * get_date_layer() {
  return s_date_layer;
}

TextLayer * get_weekday_layer() {
  return s_weekday_layer;
}

void convertToUpperCase(char *sPtr, int n)
{
  while(*sPtr != '\0' && n-- > 0)
  {
    if (*sPtr >= 'a' && *sPtr <= 'z')
      *sPtr -= 32;
    sPtr++;
  }
}

// Copy date into buffer from tm structure and show
void set_date_layer_cur_time(struct tm *tick_time) {
  //if (s_date_inited && (tick_time->tm_hour != 0 || s_cur_time.minutes != 0 || tick_time->tm_sec > 0))
  //  return;
  
  APP_LOG(APP_LOG_LEVEL_INFO, "update date layer");
  
  // set month
  strftime(month_buffer, sizeof(month_buffer), "%b", tick_time);
  text_layer_set_text(s_month_layer, month_buffer);
  convertToUpperCase(month_buffer, sizeof(month_buffer));
  // set date
  strftime(date_buffer, sizeof(date_buffer), "%d", tick_time);
  text_layer_set_text(s_date_layer, date_buffer);
  convertToUpperCase(date_buffer, sizeof(date_buffer));
  // set weekday
  strftime(weekday_buffer, sizeof(weekday_buffer), "%a", tick_time);
  text_layer_set_text(s_weekday_layer, weekday_buffer);
  convertToUpperCase(weekday_buffer, sizeof(weekday_buffer));
  
  s_date_inited = true;
}

// Release
void release_date_layer() {
  fonts_unload_custom_font(s_text_font);
}



