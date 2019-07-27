#pragma once
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "global.h"
#include "object.h"

namespace rmas {
	class Obstacle : public Circle{
		friend class Environment;
		bool has_been_hit = false;
	public:
		Obstacle(double i_x, double i_y, double radius = DEFAULT_OBSTACLE_RADIUS): 
			Circle(i_x, i_y, radius) {}
	};
}

#endif