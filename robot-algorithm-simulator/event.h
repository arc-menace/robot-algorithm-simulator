#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "robot.h"
#include <string>

namespace rmas {
	class Event {
	public:
		double x, y, orientation;
		Event(double init_x, double init_y, double init_orientation) {
			x = init_x;
			y = init_y;
			orientation = init_orientation;
		}
	};
}

#endif