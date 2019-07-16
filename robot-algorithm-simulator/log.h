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
		void print_log() {
			std::cout << "X\tY\tOrientation"<< std::endl;
			for (int i = 0; i < event_log.size(); i++) {
				std::cout << event_log[i].x << "\t";
				std::cout << event_log[i].y << "\t";
				std::cout << event_log[i].orientation << char(248) << std::endl;
			}
		}
		int write_log() {
			std::ofstream outf("rmas-sim-" + std::to_string(count) + ".csv");
			if (!outf) {
				return 1;
			}
			outf << "X,Y,Orientation" << std::endl;
			for (int i = 0; i < event_log.size(); i++) {
				outf << event_log[i].x << ",";
				outf << event_log[i].y << ",";
				outf << event_log[i].orientation << char(248) << std::endl;
			}
			count++;
			return 0;
		}
	};
}

#endif