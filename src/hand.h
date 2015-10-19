#pragma once
#include <pebble.h>

Layer * init_hand_layer(Window *window);

static void update_hand_proc(Layer *layer, GContext *ctx);

void set_hand_cur_time(struct tm *tick_time, bool SHOW_SECOND);

