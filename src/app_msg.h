#pragma once
#include <pebble.h>

enum APP_MSG_TYPE {
  WEATHER_ICON_KEY = 0,
  WEATHER_TEMPERATURE_KEY,
  WEATHER_CITY_KEY,
};

void inbox_received_callback(DictionaryIterator *iterator, void *context);

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

