#include "gpath_draw.h"
#include "gpath_weather.h"

static GPath *s_my_path_ptr = NULL;

void draw_custom_weather_gpath(GContext *ctx, int CUSTOM_PATH_ID, GPoint origin) {
  int path_num = 0;
  const struct GPathInfo *path;
  
  switch (CUSTOM_PATH_ID) {
    case CLOUDY_DAY:
      path_num = CLOUDY_DAY_PATH_COUNT;
      path = CLOUDY_DAY_PATHS;
      break;
    
    case HEAVY_RAIN:
      path_num = HEAVY_RAIN_PATH_COUNT;
      path = HEAVY_RAIN_PATHS;
      break;
    
    case HEAVY_SNOW:
      path_num = HEAVY_SNOW_PATH_COUNT;
      path = HEAVY_SNOW_PATHS;
      break;
    
    case LIGHT_RAIN:
      path_num = LIGHT_RAIN_PATH_COUNT;
      path = LIGHT_RAIN_PATHS;
      break;
    
    case LIGHT_SNOW:
      path_num = LIGHT_SNOW_PATH_COUNT;
      path = LIGHT_SNOW_PATHS;
      break;
    
    case PARTLY_CLOUDY:
      path_num = PARTLY_CLOUDY_PATH_COUNT;
      path = PARTLY_CLOUDY_PATHS;
      break;
    
    case RAINING_AND_SNOWING:
      path_num = RAINING_AND_SNOWING_PATH_COUNT;
      path = RAINING_AND_SNOWING_PATHS;
      break;
    
    case TIMELINE_SUN:
      path_num = TIMELINE_SUN_PATH_COUNT;
      path = TIMELINE_SUN_PATHS;
      break;
    
    case TIMELINE_WEATHER:
      path_num = TIMELINE_WEATHER_PATH_COUNT;
      path = TIMELINE_WEATHER_PATHS;
      break;
    
    default:
      path_num = -1;
      path = TIMELINE_WEATHER_PATHS;
      break;
  }
  
  // Draw GPath
  for (int i = 0; i < path_num; i++) {
    s_my_path_ptr = gpath_create(&path[i]);
    gpath_move_to(s_my_path_ptr, origin);
    
    // Fill the path:
    graphics_context_set_fill_color(ctx, GColorBlack);
    gpath_draw_filled(ctx, s_my_path_ptr);
    // Stroke the path:
    graphics_context_set_stroke_color(ctx, GColorWhite);
    graphics_context_set_stroke_width(ctx, 1);
    gpath_draw_outline(ctx, s_my_path_ptr);
  }
}

void custom_weather_gpath_destroy() {
  gpath_destroy(s_my_path_ptr);
}

