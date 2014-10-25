#include <pebble.h>
#include <job_watch.h>

void TOOL_editTextLayer(TextLayer * text_layer, char text[] , GTextAlignment align ){
  text_layer_set_text(text_layer, text);
  text_layer_set_text_alignment(text_layer, align);
}
