#pragma once
#include <pebble.h>

enum CUSTOM_PATH_ID_TYPE {
  CLOUDY_DAY = 0,
  HEAVY_RAIN,
  HEAVY_SNOW,
  LIGHT_RAIN,
  LIGHT_SNOW,
  PARTLY_CLOUDY,
  RAINING_AND_SNOWING,
  TIMELINE_SUN,
  TIMELINE_WEATHER,
};

void draw_custom_weather_gpath(GContext *ctx, int CUSTOM_PATH_ID, GPoint origin);

void custom_weather_gpath_destroy();
