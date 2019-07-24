#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "robot.h"
#include "block.h"

namespace Event {

	class Base {
	public:
		int index;
		std::string context_line = "Undefined";
		virtual void print_event() = 0;
		virtual void write_event(std::string filename) = 0;
		Base() = default;
	};
	//find way to use template to use for obstacles and blocks and mothership
	//Add base class Event and make other classes derived classes
	//use virtual functions to redefine functions from base class to suit each class
	class Move : Base {
	private:
		double event_x, event_y, event_orientation;
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
		
		double return_x() { return event_x; }
		double return_y() {	return event_y; }
		double return_orientation() { return event_orientation; }
	};
	class Block_Created : Base {
	private:
		rmas::Block block;
		std::string context_line = "Blocks Created: ";
	public:
		Block_Created(int ind, rmas::Block i_block) {
			index = ind;
			rmas::Block block(i_block.return_x(), i_block.return_y());
		}
		void print_event() {
			std::cout << "Block " << block.return_id() << " created at (" 
				<< block.return_x() << "," << block.return_y() << ")" << std::endl;
		}
		void write_event(std::string filename) {
			return;
		}
	};

	class Block_Picked_Up : Base {
	private:
		rmas::Block block;
		std::string context_line = "Blocks Picked Up: ";
	public:
		Block_Picked_Up(int ind, rmas::Block i_block) {
			block = i_block;
			index = ind;
		}
		void print_event() {
			std::cout << "Picked up ";
			block.print_atts();
		}
		void write_event(std::string filename) {
			return;
		}
	};
}

#endif