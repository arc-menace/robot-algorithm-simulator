#pragma once
#ifndef LOG_H
#define LOG_H

#include "event.h"
#include <vector>
#include <iostream>
#include <fstream>

namespace rmas {
	template <typename event_type>
	class Log {
	private:
		std::vector<event_type> event_log;
		int count = 0;
	public:
		void add_event(event_type new_event) {
			event_log.push_back(new_event);
		}

		event_type return_event() {
			return event_log[count];
			count++;
		}

		void print_log() {
			std::cout << event_log[0].context_line << std::endl;
			for (int i = 0; i < event_log.size(); i++) {
				event_log[i].print_event();
				std::cout << std::endl;
			}
		}

		int write_log() {
			std::ofstream outf("rmas-sim-" + std::to_string(count) + ".csv");
			if (!outf) {
				return 1;
			}
			outf << event_log[0].context_line << std::endl;
			for (int i = 0; i < event_log.size(); i++) {
				event_log[i].write_event();
			}
			count++;
			return 0;
		}
	};
}

#endif