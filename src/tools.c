#include <pebble.h>
#include <job_watch.h>

void TOOL_editTextLayer(TextLayer * text_layer, char text[] , GColor text_color, GTextAlignment align ){
  text_layer_set_text(text_layer, text);
  text_layer_set_text_alignment(text_layer, align);
  text_layer_set_text_color(text_layer, text_color);
  text_layer_set_background_color(text_layer, GColorClear);
}

void TOOL_voDrawTimeline(GContext *ctx, int16_t minutes , char project[])
{
  int8_t const X_SIZE = 110;
  int8_t const Y_SIZE = 20;
  int8_t const X_OFFSET = 17;
  int8_t const Y_OFFSET = 5;
  int8_t const X_ONE_HOUR = X_SIZE/8;
  int8_t arrow_pos = (X_SIZE * (((minutes*100) + (8*60)/2)) / (8*60)) / 100;

  /*Draw timeline*/
  graphics_draw_line(ctx, GPoint(X_OFFSET, Y_OFFSET), GPoint(X_OFFSET,Y_OFFSET+Y_SIZE));
  graphics_draw_line(ctx, GPoint(X_OFFSET, Y_OFFSET+(Y_SIZE/2)), GPoint(X_OFFSET+X_SIZE,Y_OFFSET+(Y_SIZE/2)));
  graphics_draw_line(ctx, GPoint(X_OFFSET+X_SIZE,Y_OFFSET), GPoint(X_OFFSET+X_SIZE,Y_OFFSET+Y_SIZE));
  graphics_draw_rect(ctx, GRect(X_OFFSET+(X_SIZE/2)-(X_ONE_HOUR/2),Y_OFFSET+(Y_SIZE/4),X_ONE_HOUR,(Y_SIZE/2)));

  /* Draw progress*/
  graphics_draw_line(ctx, GPoint(X_OFFSET, Y_OFFSET+(Y_SIZE/2)-1), GPoint(X_OFFSET + arrow_pos,Y_OFFSET+(Y_SIZE/2)-1));
  graphics_draw_line(ctx, GPoint(X_OFFSET, Y_OFFSET+(Y_SIZE/2)+1), GPoint(X_OFFSET + arrow_pos,Y_OFFSET+(Y_SIZE/2)+1));

  /*Show active project*/
  graphics_draw_text(ctx, project, fonts_get_system_font(FONT_KEY_GOTHIC_14),
                          GRect(X_OFFSET, Y_OFFSET + Y_SIZE, X_SIZE, 16),
                          GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}


void TOOL_voDrawTransport(GContext *ctx)
{
  int8_t const X_OFFSET = 12;
  GBitmap* img_bus = gbitmap_create_with_resource(RESOURCE_ID_IMG_BUS);
  graphics_draw_bitmap_in_rect(ctx, img_bus, GRect(X_OFFSET,20,45,30));
  graphics_draw_text(ctx, "758", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD),
      GRect(X_OFFSET,0,45,20),
      GTextOverflowModeFill, GTextAlignmentCenter, NULL);
}
