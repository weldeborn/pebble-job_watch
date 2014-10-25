#include <pebble.h>
#include <tool.h>
#include <job_watch.h>
#include <storage.h>

typedef enum DataFromPhoneKey {
  CMD_CFG_PROJECT_1 = 0x0,         // TUPLE_CSTRING
  CMD_CFG_PROJECT_2 = 0x1,         // TUPLE_CSTRING
  CMD_CFG_PROJECT_3 = 0x2,         // TUPLE_CSTRING
  CMD_CFG_VIB_7_WORK = 0x3,         // TUPLE_CSTRING
  CMD_CFG_VIB_7_HOME = 0x4,         // TUPLE_CSTRING
  CMD_SEND_CONFIG_PARAMS = 0x5,         // Request sent from phone (during configure)
} enCommands;


static Window *window;
static TextLayer *time_layer;
static Layer *timeline_layer;
static Layer *transport_layer;

static AppSync sync;
static uint8_t sync_buffer[64];



static void sync_error_callback(DictionaryResult dict_error, AppMessageResult app_message_error, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "App Message Sync Error: %d", app_message_error);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(time_layer, "Up (Show project menu)");
}

static void long_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(time_layer, "Long Up (Show history)");
}


static void timeline_layer_update_callback(Layer *me, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  TOOL_voDrawTimeline(ctx, 7*60, STORE_getProjectName_1()); //TODO: active project here instead
}

static void transport_layer_update_callback(Layer *me, GContext *ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_context_set_stroke_color(ctx, GColorWhite);
  TOOL_voDrawTransport(ctx);
}


static void send_cmd(enCommands cmd) {
  switch(cmd)
  {
    case CMD_SEND_CONFIG_PARAMS:;
      Tuplet project_1 = TupletCString(CMD_CFG_PROJECT_1, STORE_getProjectName_1());
      Tuplet project_2 = TupletCString(CMD_CFG_PROJECT_2, STORE_getProjectName_2());
      Tuplet project_3 = TupletCString(CMD_CFG_PROJECT_3, STORE_getProjectName_3());

      DictionaryIterator *iter;
      app_message_outbox_begin(&iter);

      if (iter == NULL) {
        return;
      }

      dict_write_tuplet(iter, &project_1);
      dict_write_tuplet(iter, &project_2);
      dict_write_tuplet(iter, &project_3);
      dict_write_end(iter);

      app_message_outbox_send();
      break;

    default:
      break;
  }
}

/* Called after user has submitted configuration */
static void sync_tuple_changed_callback(const uint32_t key, const Tuple* new_tuple, const Tuple* old_tuple, void* context) {
  switch (key) {
    case CMD_CFG_PROJECT_1:
      STORE_setProjectName_1(new_tuple->value->cstring);
      layer_mark_dirty(timeline_layer);
      break;

    case CMD_CFG_PROJECT_2:
      STORE_setProjectName_2(new_tuple->value->cstring);
      break;

    case CMD_CFG_PROJECT_3:
      STORE_setProjectName_3(new_tuple->value->cstring);
      break;

    case CMD_CFG_VIB_7_WORK:
      STORE_voSetVibrate7MinBeforeWork((bool) new_tuple->value->uint8);
      break;

    case CMD_CFG_VIB_7_HOME:
      STORE_voSetVibrate7MinBeforeHome((bool) new_tuple->value->uint8);
      break;

    case CMD_SEND_CONFIG_PARAMS:
      send_cmd(CMD_SEND_CONFIG_PARAMS);
      break;
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  timeline_layer = layer_create(GRect(0, 0, bounds.size.w, 50));
  layer_set_update_proc(timeline_layer, timeline_layer_update_callback);
  layer_add_child(window_layer, timeline_layer);

  transport_layer = layer_create(GRect(0, 168-50, bounds.size.w, 50));
  layer_set_update_proc(transport_layer, transport_layer_update_callback);
  layer_add_child(window_layer, transport_layer);

  time_layer = text_layer_create(GRect(0,72,bounds.size.w, 20));
  TOOL_editTextLayer(time_layer, "Press any key", GColorWhite, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(time_layer));

  Tuplet initial_values[] = {
      TupletCString(CMD_CFG_PROJECT_1, STORE_getProjectName_1()),
      TupletCString(CMD_CFG_PROJECT_2, STORE_getProjectName_2()),
      TupletCString(CMD_CFG_PROJECT_3, STORE_getProjectName_3())
  };

  app_sync_init(&sync, sync_buffer, sizeof(sync_buffer), initial_values, ARRAY_LENGTH(initial_values),
      sync_tuple_changed_callback, sync_error_callback, NULL);
}

static void window_unload(Window *window) {
  app_sync_deinit(&sync);
  text_layer_destroy(time_layer);
  layer_destroy(timeline_layer);
  layer_destroy(transport_layer);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 500, long_up_click_handler, NULL);
}

static void init(void) {
  window = window_create();
  window_set_fullscreen(window, true);
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
  window_set_background_color(window, GColorBlack);

  const int inbound_size = 128;
  const int outbound_size = 128;
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
