#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

namespace rmas {
	class Obstacle {
		friend class Move;
		double x, y; //Location on map.
		double radius = 0.75;
	public:
		Obstacle(double x_coordinate, double y_coordinate) {
			x = x_coordinate;
			y = y_coordinate;
		}
		double return_x(){
			return x;
		}
		double return_y() {
			return y;
		}
		double return_radius() {
			return radius;
		}
	};
}

#endif