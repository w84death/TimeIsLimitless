/*
*
*
*   P1X, Krzysztof Jankowski
*   Time Is Limitless
*
*   abstract: Watch face for Pebble
*   created: 11-09-2014
*   license: do what you want and dont bother me
*
*   webpage: http://p1x.in
*   twitter: @w84death
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <pebble.h>
#include <face.h>

AppTimer *timer;
static int show_time_delay = 1250;
static bool show_time = false;
static char the_time[] = "00:00";
static int last_h = 0;

void timer_callback(void *data) {
	show_message("");
	show_time = false;
}

void accel_tap_handler(AccelAxisType axis, int32_t direction) {
	show_time = !show_time;
	if(show_time){
		show_message(the_time);
		timer = app_timer_register(show_time_delay, (AppTimerCallback)timer_callback, NULL);
	}else{
		show_message("");
		show_time = false;
	}
}

void vibrate(){
	static const uint32_t const segments[] = { 20, 200, 50 };
	VibePattern pattern = {
		.durations = segments,
		.num_segments = ARRAY_LENGTH(segments),
	};
	vibes_enqueue_custom_pattern(pattern);	
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
	if(units_changed & HOUR_UNIT){
		vibrate();
	}
  strftime(the_time, sizeof("00:00"), "%H:%M", tick_time);
	if(show_time){
		show_message(the_time);
	}
}

void handle_init(void) {
	show_face();
	show_message("");
	accel_tap_service_subscribe(accel_tap_handler);
	tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler)tick_handler);
}

void handle_deinit(void) {
  hide_face();
	app_timer_cancel(timer);
	accel_tap_service_unsubscribe();
	tick_timer_service_unsubscribe();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
