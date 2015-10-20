#pragma once
#include <pebble.h>

void init_weather_layer(Window *window);
Layer * get_weather_layer();

static void update_weather_proc(Layer *layer, GContext *ctx);

void release_weather_layer();

