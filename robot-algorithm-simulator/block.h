#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "object.h"

namespace rmas {
	class Block : public Rectangle {
	private:
		friend class Move;
		friend class Environment;

		double stated_x = 0;
		double stated_y = 0;
		char id = 'Z'; //A, B, C, D, E, or F

	public:
		Block(double i_stated_x = 0, double i_stated_y = 0, double i_x = 0, double i_y = 0,
			char i_id = 'Z', double orient = 0, double width = 1.50) :
			Rectangle(i_x, i_y, width, width, orient, "Block"),
			stated_x(i_stated_x), stated_y(i_stated_y), id(i_id) {}

		void print_atts() {
			std::cout << "Block " << id << " at (" << x << ", " << y << ")" << std::endl;
		}
		char return_id() { return id; }
	};
}

#endif