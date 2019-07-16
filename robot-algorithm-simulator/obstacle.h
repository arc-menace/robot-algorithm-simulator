#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

namespace rmas {
	class Obstacle {
		friend class Move;
		double x, y; //Location on map.
	public:
		Obstacle(double x_coordinate, double y_coordinate) {
			x = x_coordinate;
			y = y_coordinate;
		}
	};
}

#endif