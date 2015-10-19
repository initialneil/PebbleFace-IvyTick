#pragma once
#include <pebble.h>

void init_date_layer(Window *window);
TextLayer * get_month_layer();
TextLayer * get_date_layer();
TextLayer * get_weekday_layer();

void set_date_layer_cur_time(struct tm *tick_time);

void release_date_layer();

