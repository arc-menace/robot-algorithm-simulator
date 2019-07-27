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
		int log_count = 0;
	public:
		void add_event(event_type new_event, bool silent = false) {
			event_log.push_back(new_event);
			if (!silent) {
				new_event.print_event();
			}
		}

		event_type return_event(int count) {
			if (count >= event_log.size()) {
				count = event_log.size() - 1;
			}
			return event_log[count];
		}

		int return_size() {
			return event_log.size();
		}

		void print_log() {
			std::cout << event_log[0].context_line << std::endl;
			for (int i = 0; i < event_log.size(); i++) {
				event_log[i].print_event();
				std::cout << std::endl;
			}
		}


		//Write log function does not work currently
		int write_log() {
			std::ofstream outf("rmas-sim-" + std::to_string(log_count) + ".csv");
			if (!outf) {
				return 1;
			}
			outf << event_log[0].context_line << std::endl;
			outf.close();
			for (int i = 0; i < event_log.size(); i++) {
				event_log[i].write_event("rmas-sim-" + std::to_string(log_count) + ".csv");
			}
			log_count++;
			return 0;
		}
	};
}

#endif