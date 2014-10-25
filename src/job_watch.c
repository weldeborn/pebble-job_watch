#include <pebble.h>
#include <tool.h>
#include <job_watch.h>

static Window *window;

static TextLayer *text_layer;

static Layer *timeline_layer;


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
  TOOL_voDrawTimeline(ctx, 4*60, "USFACELIFT");
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  timeline_layer = layer_create(GRect(0, 0, bounds.size.w, 50));
  layer_set_update_proc(timeline_layer, timeline_layer_update_callback);
  layer_add_child(window_layer, timeline_layer);

  text_layer = text_layer_create((GRect) ConstantGRect(0,72,bounds.size.w, 20));
  TOOL_editTextLayer(text_layer, "Press any key", GColorWhite, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
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
