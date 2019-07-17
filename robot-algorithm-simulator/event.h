#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <fstream>
#include <string>
#include <iostream>
#include "robot.h"

namespace Event {
	//find way to use template to use for obstalces and blocks and mothership
	//Add base class Event and make other classes derived classes
	//use virtual functions to redefine functions from base class to suit each class
	class Move {
	private:
		double event_x, event_y, event_orientation;
		int index;
	public:
		std::string context_line = "Index\tX\tY\tOrientation"; //X	 Y  Orientation

		Move(int ind, rmas::Robot robot) {
			index = ind;
			event_x = robot.return_x();
			event_y = robot.return_y();
			event_orientation = robot.return_orientation();
		}

		void print_event() {
			std::cout << index << "\t" << event_x << "\t" << event_y << "\t" << event_orientation << char(248) << std::endl;
		}

		void write_event(std::string filename) {
			std::ofstream outf(filename);
			outf << index << "," << event_x << "," << event_y << "," << event_orientation << char(248) << std::endl;
			outf.close();
		}
		
		double return_x() {
			return event_x;
		}

		double return_y() {
			return event_y;
		}

		double return_orientation() {
			return event_orientation;
		}
	};
}

#endif