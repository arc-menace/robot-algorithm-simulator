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
	class Event {
	public:
		int index;
		double event_x, event_y, event_orientation;
		std::string context_line = "No Context line for Base Class";

		Event() : index(0), event_x(0), event_y(0), event_orientation(0) {}

		virtual void print_event() = 0;

		//virtual void write_event(std::ofstream& outf) = 0;

		int return_index() { return index; }
	};

	class Move : public Event {
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

		void write_event(std::ofstream outf) {
			outf << index << "," << event_x << "," << event_y << "," << event_orientation << char(248) << std::endl;
		}

		std::vector<double> return_atts() {
			std::vector<double>return_vals;
			return_vals.push_back(event_x);
			return_vals.push_back(event_y);
			return_vals.push_back(event_orientation);
			return return_vals;
		}
	};

	class Block_Creation : public Event{
	private:
		rmas::Block block;
		double event_x, event_y, event_orientation;
		char id = 'W';
	public:
		Block_Creation(int ind, rmas::Block i_block) : block(i_block) {
			index = ind;
			event_x = block.return_x();
			event_y = block.return_y();
			event_orientation = block.return_orientation();
			id = block.return_id();
		}

		void print_event() {
			std::cout << index << "\t" << block.return_name() << " " << block.return_id() 
				<< " has been created at (" << block.return_x() << "," << block.return_y() 
				<< ")" << std::endl;
		}

		void write_event(std::ofstream& outf) {
			outf << index << "\tBlock " << block.return_id() << " created at (" << block.return_x() 
				<< "," << block.return_y() << ")" << std::endl;
		}
		std::vector<double> return_atts() {
			std::vector<double>return_vals;
			return_vals.push_back(event_x);
			return_vals.push_back(event_y);
			return_vals.push_back(event_orientation);
			return return_vals;
		}
	};

	class Robot_Creation {
	private:
		int index = 0;
		rmas::Robot robot;
	public:
		Robot_Creation(int ind, rmas::Robot i_robot) : robot(i_robot) {
			index = ind;
		}

		void print_event() {
			std::cout << index << "\tA " << robot.return_name() << " has been created at (" << robot.return_x() << "," << robot.return_y() << ")" << std::endl;
		}

		void write_event() {
			return;
		}
	};

	class Obstacle_Creation {
	private:
		int index = 0;
		rmas::Obstacle obst;
	public:
		Obstacle_Creation(int ind, rmas::Obstacle i_obst) : obst(i_obst) {
			index = ind;
		}

		void print_event() {
			std::cout << index << "\tAn " << obst.return_name() << " has been created at (" << obst.return_x() << "," << obst.return_y() << ")" << std::endl;
		}

		void write_event() {
			return;
		}
	};
}

#endif