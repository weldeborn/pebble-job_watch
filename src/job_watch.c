#include <pebble.h>
#include <tool.h>
#include <job_watch.h>
#include <storage.h>

enum DataFromPhoneKey {
  CFG_PROJECT_1 = 0x0,         // TUPLE_CSTRING
  CFG_PROJECT_2 = 0x1,         // TUPLE_CSTRING
  CFG_PROJECT_3 = 0x2,         // TUPLE_CSTRING
};


static Window *window;
static TextLayer *text_layer;
static Layer *timeline_layer;

static AppSync sync;
static uint8_t sync_buffer[64];

static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up (Show project menu)");
}

static void long_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Long Up (Show history)");
}


static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 500, long_up_click_handler, NULL);
}

static void timeline_layer_update_callback(Layer *me, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  TOOL_voDrawTimeline(ctx, 4*60, STORE_getProjectName_1());
}

static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
  switch (key) {
    case CFG_PROJECT_1:
      STORE_setProjectName_1(new_tuple->value->cstring);
      layer_mark_dirty(timeline_layer);
      break;

    case CFG_PROJECT_2:
      STORE_setProjectName_2(new_tuple->value->cstring);
      break;

    case CFG_PROJECT_3:
      STORE_setProjectName_3(new_tuple->value->cstring);
      break;
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  timeline_layer = layer_create(GRect(0, 0, bounds.size.w, 50));
  layer_set_update_proc(timeline_layer, timeline_layer_update_callback);
  layer_add_child(window_layer, timeline_layer);

  text_layer = text_layer_create(GRect(0,72,bounds.size.w, 20));
  TOOL_editTextLayer(text_layer, "Press any key", GColorWhite, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  Tuplet initial_values[] = {
      TupletCString(CFG_PROJECT_1, STORE_getProjectName_1()),
      TupletCString(CFG_PROJECT_2, STORE_getProjectName_2()),
      TupletCString(CFG_PROJECT_3, STORE_getProjectName_3())
  };

  app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, sync_error_callback, NULL);
}

static void window_unload(Window *window) {
  app_sync_deinit(&sync);
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_fullscreen(window, true);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  window_set_background_color(window, GColorBlack);

  const int inbound_size = 64;
  const int outbound_size = 64;
  app_message_open(inbound_size, outbound_size);

}

static void deinit(void) {
  window_destroy(window);

}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
