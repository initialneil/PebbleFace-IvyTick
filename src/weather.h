#pragma once
#include <pebble.h>

void init_weather_layer(Window *window);
Layer * get_weather_layer();
TextLayer * get_temperature_layer();
TextLayer * get_city_layer();

static void update_weather_proc(Layer *layer, GContext *ctx);

void update_weather_layer(char * conditions_buffer, char *temperature_buffer, char *city_buffer);
void update_weather_with_app_msg(struct tm *tick_time);

void release_weather_layer();

