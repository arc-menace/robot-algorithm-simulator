#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "object.h"

namespace rmas {
	class Block {
	private:
		friend class Move;
		friend class Environment;
		//double stated_x; //Location
		//double stated_y; //on map.
		double orientation = 0;
		float width = 1.50;
		bool has_been_hit = false;
		bool is_picked_up = false;
		Shape shape = Shape::SQUARE;
		char id = '0'; //i.e. A, B, C, D, E, or F

		//According to the official rules of the competition, the locations of the blocks as given to the team
		//before the round begins are within the square foot area around their stated location. This can be
		//simulated by adding or subtracting up to 6 inches in either axis.

		double return_rand(int max, double min) {
			srand(time(0));
			double random_num = rand() % max + min; //needs to be changed to allow for decimal numbers
			return random_num;
		}

		double x;// = stated_x; //+ return_rand(6, -6.0); //This gives the block an accuracy within 1 sq. foot of the correct location
		double y;// = stated_y; //+ return_rand(6, -6.0);

	public:
		Block() = default;
		Block(double x_coordinate, double y_coordinate) { //Block Object constructor
			x = x_coordinate;
			y = y_coordinate;
		}
		void picked_up() {
			is_picked_up = true;
		}
		double return_x() {
			return x;
		}
		double return_y() {
			return y;
		}
		double return_width() {
			return width;
		}
		double return_length() { //redundant I know...
			return width;
		}
		void print_atts() {
			std::cout << "Block " << id << " at (" << x << ", " << y << ")" << std::endl;
		}
		Shape return_shape() {
			return shape;
		}
		double return_radius() {
			return 0;
		}
		char return_id() {
			return id;
		}
		double return_orient() {
			return orientation;
		}
	};
}

#endif