#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "rmas6219.h"
#include "return_rand.h"

class Block {
	double stated_x = 0;
	double stated_y = 0; //Location on map.
public:
	Block(double x_coordinate, double y_coordinate) {
		stated_x = x_coordinate;
		stated_y = y_coordinate;
	}

	double actual_x = stated_x + return_rand (6, -6);
	double actual_y = stated_y + return_rand (6, -6);
};

#endif BLOCK_H