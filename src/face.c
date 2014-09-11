#include "face.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_infinity_white;
static GFont s_res_gothic_28_bold;
static TextLayer *s_textlayer_title;
static BitmapLayer *s_bitmaplayer_infinity;
static TextLayer *s_textlayer_message;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_infinity_white = gbitmap_create_with_resource(RESOURCE_ID_infinity_white);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_textlayer_title
  s_textlayer_title = text_layer_create(GRect(0, 140, 144, 14));
  text_layer_set_background_color(s_textlayer_title, GColorClear);
  text_layer_set_text_color(s_textlayer_title, GColorWhite);
  text_layer_set_text(s_textlayer_title, "Time is limitless.");
  text_layer_set_text_alignment(s_textlayer_title, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_title);
  
  // s_bitmaplayer_infinity
  s_bitmaplayer_infinity = bitmap_layer_create(GRect(47, 74, 50, 20));
  bitmap_layer_set_bitmap(s_bitmaplayer_infinity, s_res_infinity_white);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_infinity);
  
  // s_textlayer_message
  s_textlayer_message = text_layer_create(GRect(0, 14, 144, 28));
  text_layer_set_background_color(s_textlayer_message, GColorClear);
  text_layer_set_text_color(s_textlayer_message, GColorWhite);
  text_layer_set_text(s_textlayer_message, "00:00");
  text_layer_set_text_alignment(s_textlayer_message, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_message, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_message);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_title);
  bitmap_layer_destroy(s_bitmaplayer_infinity);
  text_layer_destroy(s_textlayer_message);
  gbitmap_destroy(s_res_infinity_white);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

// CHANGE UX

void show_message(char *msg){
	text_layer_set_text(s_textlayer_message, msg);
}

// INIT/DEINIT
void show_face(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_face(void) {
  window_stack_remove(s_window, true);
}

