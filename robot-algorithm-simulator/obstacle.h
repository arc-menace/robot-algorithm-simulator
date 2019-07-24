#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "object.h"

namespace rmas {
	class Obstacle {
		friend class Move;
		double x, y; //Location on map.
		double radius = 0.75;
		Shape shape = Shape::CIRCLE;
		bool has_been_hit = false;
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
		Shape return_shape() {
			return shape;
		}
	};
}

#endif