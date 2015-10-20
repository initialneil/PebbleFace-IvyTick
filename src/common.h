#pragma once

// common type and data
typedef struct {
  int hours;
  int minutes;
  int seconds;
} Time;

#define COLORS true
//#define SHOW_SCREENSHOT
#define COLOR_PRESET 0

#if COLOR_PRESET == 0

// panel color
#define MINUTE_DOTS_COLOR GColorLightGray
#define HOUR_DOTS_COLOR GColorLightGray

#define PANEL_IN_COLOR GColorBlack
#define PANEL_OUT_COLOR GColorBlack

// hand color
#define HOUR_HAND_COLOR GColorWhite
#define HOUR_HAND_INSIDE_COLOR GColorBlack

#define MINUTE_HAND_COLOR GColorYellow
#define MINUTE_HAND_INSIDE_COLOR GColorBlack

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorWhite
#define CENTER_DOT_IN_COLOR GColorBlack

// month
#define MONTH_COLOR GColorWhite
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorFolly
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorVividCerulean
#define WEEKDAY_BACKGROUND_COLOR GColorClear

#elif COLOR_PRESET == 1

// panel color
#define MINUTE_DOTS_COLOR GColorLightGray
#define HOUR_DOTS_COLOR GColorDarkGray

#define PANEL_IN_COLOR GColorWhite
#define PANEL_OUT_COLOR GColorWhite

// hand color
#define HOUR_HAND_COLOR GColorBlack
#define HOUR_HAND_INSIDE_COLOR GColorWhite

#define MINUTE_HAND_COLOR GColorYellow
#define MINUTE_HAND_INSIDE_COLOR GColorWhite

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorBlack
#define CENTER_DOT_IN_COLOR GColorWhite

// month
#define MONTH_COLOR GColorBlack
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorBlueMoon
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorRoseVale
#define WEEKDAY_BACKGROUND_COLOR GColorClear

#elif COLOR_PRESET == 2

// panel color
#define MINUTE_DOTS_COLOR GColorChromeYellow
#define HOUR_DOTS_COLOR GColorChromeYellow

#define PANEL_IN_COLOR GColorBlack
#define PANEL_OUT_COLOR GColorBlack

// hand color
#define HOUR_HAND_COLOR GColorWhite
#define HOUR_HAND_INSIDE_COLOR GColorBlack

#define MINUTE_HAND_COLOR GColorWhite
#define MINUTE_HAND_INSIDE_COLOR GColorBlack

#define SECOND_HAND_COLOR GColorChromeYellow

// center dot color
#define CENTER_DOT_COLOR GColorWhite
#define CENTER_DOT_IN_COLOR GColorBlack

// month
#define MONTH_COLOR GColorVividCerulean
#define MONTH_BACKGROUND_COLOR GColorClear

// date
#define DATE_COLOR GColorVividCerulean
#define DATE_BACKGROUND_COLOR GColorClear

// weekday
#define WEEKDAY_COLOR GColorVividCerulean
#define WEEKDAY_BACKGROUND_COLOR GColorClear

#endif



