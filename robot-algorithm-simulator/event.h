#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "rmas6219.h"

namespace rmas {
	class Event {
	private:
		enum class EventType {
			MOVEMENT,
			STOP,
			COLLISION,
			CAPTURE,
			SCORE,
			FALL,
			INSTANTIATE,
			RETURN,
			ERROR,
			SYSTEM
		};

		EventType type = EventType::SYSTEM; //different types have different permissions
		string event_message = "Log message not set."; //Message saved to print or write for the user to see
		string tag = "system"; //used to find the object later. Will be concatenated with a number upon creation

		bool write = true; //whether the event should be written to a log file. True by default
		bool print = true; //whether the event should be printed to the command line. True by default
		bool edit_score = false; //whether an event can alter the score. False by default
		bool edit_time = false;
		bool end_sim = false;

	public:
		Event(EventType type, string tag, string message, bool silent = false);

		void determine_display(EventType type) {
			switch(type){
			case EventType::MOVEMENT:
			case EventType::STOP:
				write = true;
				print = true;
				edit_score = false;
				edit_time = false;
				end_sim = false;
			case EventType::COLLISION:
			case EventType::CAPTURE:
				write = true;
				print = true;
				edit_score = true;
				edit_time = false;
				end_sim = false;
			case EventType::FALL:
				write = true;
				print = true;
				edit_score = false;
				edit_time = true;
				end_sim = true;
			case EventType::SYSTEM:
			case EventType::INSTANTIATE:
				write = false;
				print = true;
				edit_score = false;
				edit_time = false;
				end_sim = false;
			case EventType::ERROR:
				write = false;
				print = true;
				edit_score = false;
				edit_time = false;
				end_sim = true;
			case EventType::RETURN:
			default:
				write = true;
				print = true;
				edit_score = true;
				edit_time = true;
				end_sim = true;
			}
		}
	};
}

#endif