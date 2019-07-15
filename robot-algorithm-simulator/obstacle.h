#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

namespace rmas {
	class Obstacle {
		double stated_x, stated_y; //Location on map.
	public:
		Obstacle(double x_coordinate, double y_coordinate) {
			stated_x = x_coordinate;
			stated_y = y_coordinate;
		}
	};
}

#endif