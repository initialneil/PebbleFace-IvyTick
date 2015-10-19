#pragma once
#include <pebble.h>

Layer * init_panel_layer(Window *window);

static void update_panel_proc(Layer *layer, GContext *ctx);

