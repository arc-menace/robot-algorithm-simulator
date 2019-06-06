#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "rmas6219.h"
#include "return_rand.h"

class Block {
	double stated_x = 0; //Location
	double stated_y = 0; //on map.
public:
	Block(double x_coordinate, double y_coordinate) { //Block Object constructor
		stated_x = x_coordinate;
		stated_y = y_coordinate;
	}


	//According to the official rules of the competition, the locations of the blocks as given to the team
	//before the round begins are within the square foot area around their stated location. This can be
	//simulated by adding or subtracting up to 6 inches in either axis.

	double actual_x = stated_x + return_rand (6, -6.0); 
	double actual_y = stated_y + return_rand (6, -6.0);
};

#endif BLOCK_H