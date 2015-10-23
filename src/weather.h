#pragma once
#include <pebble.h>

void init_weather_layer(Window *window);
Layer * get_weather_layer();
TextLayer * get_temperature_layer();
TextLayer * get_city_layer();

void config_weather_layer(bool show_weather, bool show_location);
void get_weather_config(bool *show_weather, bool *show_location);

void config_location_setting(char *default_location, char *location_opt);
void set_default_location(const char default_location[]);
void set_location_opt(const char location_opt[]);

void set_conditions_buffer(const char conditions_buffer[]);
void set_temperature_buffer(const char temperature_buffer[]);
void set_city_buffer(const char city_buffer[]);

static void update_weather_proc(Layer *layer, GContext *ctx);
void refresh_weather_display();

void config_weather_buffer(char * conditions_buffer, char *temperature_buffer, char *city_buffer);
void update_weather_with_app_msg();

void release_weather_layer();

