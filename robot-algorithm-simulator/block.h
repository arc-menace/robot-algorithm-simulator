#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <cstdlib>
#include <time.h>

namespace rmas {
	class Block {
	private:
		friend class Move;
		double stated_x = 0; //Location
		double stated_y = 0; //on map.
		double orientation = 0;
		float radius = 0.75;

		char id = '0'; //i.e. A, B, C, D, E, or F

		//According to the official rules of the competition, the locations of the blocks as given to the team
		//before the round begins are within the square foot area around their stated location. This can be
		//simulated by adding or subtracting up to 6 inches in either axis.

		double return_rand(int max, double min) {
			srand(time(0));
			double random_num = rand() % max + min;
			return random_num;
		}

		double x = stated_x + return_rand(6, -6.0); //This gives the block an accuracy within 1 sq. foot of the correct location
		double y = stated_y + return_rand(6, -6.0);

	public:
		Block(double x_coordinate, double y_coordinate) { //Block Object constructor
			stated_x = x_coordinate;
			stated_y = y_coordinate;
		}

	};
}

#endif