#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "rmas6219.h"
#include <vector>

//Obstacle Class
class Obstacle {
public:
	double stated_x, stated_y; //Location on map.
	Obstacle(double x_coordinate, double y_coordinate) { //Why is this not a constructor?
		stated_x = x_coordinate;
		stated_y = y_coordinate;
	}
};

#endif OBSTACLE_H