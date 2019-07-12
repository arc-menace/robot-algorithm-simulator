#include "event.h"
#include "rmas6219.h"

rmas::Event::Event(EventType given_type, string given_tag, string message, bool silent = false, int add_score = 0) {
	type = given_type;
	determine_display(type);

	tag = given_tag;
	event_message = message;
		
	if (silent) {
		write = false;
		print = false;
	}

	if (write) {

	}
	if (print) {

	}
	if (edit_score) {

	}
	if (edit_time) {

	}
	if (end_sim) {

	}
}
